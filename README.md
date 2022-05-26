# AriesDB features

SQL database created in educational purpose. 

- CRUD operations
- data are saved into csv  files
- commands logging
- for now only CLI application, no web support
- Can be build as webServer or CLI

## ENVIRONMENT:

- boost asio
- CMake
- GoogleTest
- C++ 17

### Build

```
sh scripts/build.sh
cd build
./DB
```
### Test

```
sh scripts/unt_test.sh
```

### Additional information

- MIT license
- lot of code here could be refactored,what I'm aware of, however I prefer to go forward than focus on fixing 
- Program runs by default as webserver, after commenting WEB_SERVER flag in Config.h it can run as CLI app

### TODO:

- improve receiving and sending messages
- add JenkinsPipeline
- add port in cli
- clean code

### FUTURE IDEAS:

- accounts
- security
- reading .sql files



