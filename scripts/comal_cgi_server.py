#!/usr/bin/env python3
"""
Simple HTTP Server with COMAL CGI support
Demonstrates using COMAL programs (with SPLIT$ function) as CGI handlers
"""

import http.server
import socketserver
import subprocess
import os
import sys
from pathlib import Path

# Configuration
PORT = 8888
COMAL_PROGRAM = "samples/http_cgi.lst"
OPENCOMALRUN = "bin/opencomalrun"

class ComalCGIHandler(http.server.BaseHTTPRequestHandler):
    """HTTP request handler that executes COMAL programs as CGI"""
    
    def do_GET(self):
        """Handle GET requests by passing them to COMAL program"""
        self.handle_request()
    
    def do_POST(self):
        """Handle POST requests"""
        # For simplicity, treat POST like GET in this demo
        self.handle_request()
    
    def handle_request(self):
        """Execute COMAL program with HTTP request data"""
        try:
            # Reconstruct the request line that the COMAL program expects
            request_line = f"{self.command} {self.path} HTTP/{self.request_version.split('/')[1]}"
            
            # Build input for COMAL program
            input_data = request_line + "\n"
            
            # Add all headers
            for header, value in self.headers.items():
                input_data += f"{header}: {value}\n"
            
            # Empty line to signal end of headers
            input_data += "\n"
            
            # Find the COMAL program
            if not os.path.exists(OPENCOMALRUN):
                self.send_error(500, f"COMAL interpreter not found: {OPENCOMALRUN}")
                return
            
            if not os.path.exists(COMAL_PROGRAM):
                self.send_error(500, f"COMAL program not found: {COMAL_PROGRAM}")
                return
            
            # Execute COMAL program with stream handling
            process = subprocess.Popen(
                [OPENCOMALRUN, COMAL_PROGRAM],
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )
            
            stdout, stderr = process.communicate(input=input_data, timeout=5)
            
            if process.returncode != 0:
                self.send_error(500, f"COMAL program error: {stderr}")
                return
            
            # Parse response from COMAL program
            lines = stdout.split('\n')
            if not lines:
                self.send_error(500, "No response from COMAL program")
                return
            
            # First line should be HTTP status
            status_line = lines[0]
            if not status_line.startswith("HTTP/"):
                # If no HTTP status provided, generate one
                self.send_response(200)
                self.send_header("Content-Type", "text/html")
                self.end_headers()
                self.wfile.write(stdout.encode('utf-8'))
                return
            
            # Parse status code from response
            try:
                status_code = int(status_line.split()[1])
            except (IndexError, ValueError):
                status_code = 200
            
            self.send_response(status_code)
            
            # Process response headers
            i = 1
            content_started = False
            while i < len(lines) and not content_started:
                line = lines[i]
                if line.strip() == "":
                    content_started = True
                    i += 1
                    break
                
                if ':' in line:
                    header, value = line.split(':', 1)
                    self.send_header(header.strip(), value.strip())
                i += 1
            
            self.end_headers()
            
            # Send response body
            body = '\n'.join(lines[i:])
            if body.strip():
                self.wfile.write(body.encode('utf-8'))
        
        except subprocess.TimeoutExpired:
            self.send_error(504, "COMAL program timeout")
        except Exception as e:
            self.send_error(500, f"Server error: {str(e)}")
    
    def log_message(self, format, *args):
        """Log requests"""
        print(f"[{self.client_address[0]}] {format % args}")


def main():
    """Start the HTTP server"""
    # Change to repo directory if needed
    repo_root = Path(__file__).parent.absolute()
    os.chdir(repo_root)
    
    print(f"OpenCOMAL CGI Server")
    print(f"==================")
    print(f"COMAL interpreter: {OPENCOMALRUN}")
    print(f"COMAL program: {COMAL_PROGRAM}")
    print(f"Server: http://localhost:{PORT}")
    print()
    print("Test URLs:")
    print(f"  http://localhost:{PORT}/")
    print(f"  http://localhost:{PORT}/test?name=John&city=Oslo")
    print()
    print("Press Ctrl+C to stop.")
    print()
    
    with socketserver.TCPServer(("", PORT), ComalCGIHandler) as httpd:
        try:
            httpd.serve_forever()
        except KeyboardInterrupt:
            print("\nServer stopped.")
            sys.exit(0)


if __name__ == "__main__":
    main()
