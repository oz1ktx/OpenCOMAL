Continue later: OpenCOMAL socket-work notes

Quick resume steps
- Build binaries: `cd src && make`
- Quick pipe test: `printf $'one\n' | ./bin/opencomalrun --plain samples/filter_pipe.lst`
- Start socket helper: `scripts/serve_comal.sh -p 18080 samples/web_dbg.lst`
  then test: `curl -v http://localhost:18080/`
- Run integration test: `samples/tests/web_integration_test.sh` (starts wrapper and verifies header+body)

If server returns headers only
- Reproduce without ncat: `printf $'GET / HTTP/1.0\r\nHost: localhost\r\n\r\n' | ./bin/opencomalrun --plain samples/web_skeleton.lst`
- Check `/tmp/serve_test.log` and `/tmp/ncat*.log` for wrapper/runtime output

Files modified during the socket helper work
- `scripts/serve_comal.sh`
- `scripts/serve_wrapper.sh`
- `samples/web_dbg.lst`
- `samples/tests/web_integration_test.sh`

If you'd like me to continue later, run the integration test and paste failing logs; I will resume from where we left off.
