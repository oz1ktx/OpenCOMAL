# COMAL CGI Server Setup

This directory contains examples and tools for using COMAL programs as CGI handlers through stdin/stdout streams.

## Overview

The `opencomalrun` batch runner supports reading from stdin, making it possible to:
1. Pipe HTTP requests to COMAL programs
2. Parse request data using the new `SPLIT$` function
3. Generate HTTP responses via stdout
4. Use COMAL programs as CGI script handlers

## Example: Simple HTTP Request Parser

```comal
10 INPUT req$
20 INPUT hdr$
30 WHILE hdr$ <> "" DO
40   INPUT hdr$
50 ENDWHILE
60 m$ = SPLIT$(req$, " ", 1)
70 p$ = SPLIT$(req$, " ", 2)
80 PRINT "HTTP/1.0 200 OK"
90 PRINT "Content-Type: text/html"
100 PRINT ""
110 PRINT "<html><body>"
120 PRINT "<p>Method: "; m$; "</p>"
130 PRINT "<p>Path: "; p$; "</p>"
140 PRINT "</body></html>"
150 END
```

## Testing

### Direct Stream Test
```bash
printf "GET /test HTTP/1.0\r\n\r\n" | opencomalrun program.lst
```

### With Python Server
Create a Python HTTP server that executes COMAL programs:

```python
import subprocess
import http.server
import socketserver

class ComalHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        # Prepare request for COMAL
        request_line = f"{self.command} {self.path} HTTP/{self.request_version.split('/')[1]}"
        input_data = request_line + "\n\n"
        
        # Execute COMAL program
        process = subprocess.Popen(
            ["opencomalrun", "program.lst"],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            text=True
        )
        stdout, _ = process.communicate(input=input_data)
        
        # Parse and send response
        lines = stdout.split('\n')
        status_line = lines[0]
        # ... handle response parsing

with socketserver.TCPServer(("", 8888), ComalHandler) as httpd:
    httpd.serve_forever()
```

## SPLIT$ Function for Parsing

The new `SPLIT$` function is perfect for parsing HTTP requests:

```comal
REM Parse "GET /path?query HTTP/1.0"
method$ = SPLIT$(request$, " ", 1)      REM "GET"
path_query$ = SPLIT$(request$, " ", 2)  REM "/path?query"
protocol$ = SPLIT$(request$, " ", 3)    REM "HTTP/1.0"

REM Parse query string "key1=val1&key2=val2"
key1$ = SPLIT$(query$, "&", 1)
key2$ = SPLIT$(query$, "&", 2)

REM Extract value from "key1=val1"
key$ = SPLIT$(key1$, "=", 1)
val$ = SPLIT$(key1$, "=", 2)
```

## Important Notes

1. **Syntax Limitations**: When using SPLIT$ with semicolons (`;`) in LET statements, there can be parsing issues. Use direct assignment instead:
   ```comal
   x$ = SPLIT$(y$, ";", 1)     REM Good
   LET x$ = SPLIT$(y$, ";", 1) REM May fail
   ```

2. **Stream Mode**: The opencomalrun binary reads from stdin line-by-line, making it ideal for:
   - Processing line-based protocols (HTTP, SMTP, etc.)
   - Piped data streams
   - CGI script execution

3. **Header Parsing**: Remember to read and discard HTTP headers:
   ```comal
   20 WHILE hdr$ <> "" DO
   30   INPUT hdr$
   40 ENDWHILE
   ```

## Use Cases

- **Simple CGI Scripts**: Generate dynamic HTML from COMAL
- **Microservices**: Light-weight HTTP handlers
- **Data Processing**: Parse delimited data streams
- **Legacy Integration**: Connect COMAL programs to modern web servers

## Related Files

- `cgi_demo.lst` - Simple CGI demonstration
- `simple_cgi.lst` - Minimal HTTP server example
- `http_cgi.lst` - Full HTTP request parser with query string handling
- `comal_cgi_server.py` - Python HTTP server framework (requires enhancement)

## Future Improvements

- Better error handling for malformed requests
- Support for POST data parsing
- Cookie and session handling
- More robust SPLIT$ integration with LET statements
