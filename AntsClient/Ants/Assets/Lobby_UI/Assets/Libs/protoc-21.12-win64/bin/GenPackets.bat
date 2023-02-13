protoc.exe -I=./  --csharp_out=../../../Script/protobuf/ ./Protocol.proto
IF ERRORLEVEL 1 PAUSE