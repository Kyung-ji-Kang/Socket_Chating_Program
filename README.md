# TCP/IP Socket Communication Program

## 프로젝트 소개
C++로 구현한 TCP/IP 소켓 통신 채팅 프로그램입니다.

## 프로젝트 구조
```
Socket_Chating_Program/
├── include/          # 헤더 파일
│   ├── Server.h
│   ├── Client.h
│   └── MessageHandler.h
├── src/             # 구현 파일
│   ├── Server.cpp
│   ├── Client.cpp
│   └── MessageHandler.cpp
├── server_main.cpp  # 서버 실행 파일
├── client_main.cpp  # 클라이언트 실행 파일
├── Makefile        # 빌드 파일
└── README.md       # 프로젝트 설명
```

## 빌드 및 실행 방법
```bash
# 빌드
make

# 서버 실행
./server

# 클라이언트 실행 (다른 터미널에서)
./client
```

## 주요 기능
- 멀티 클라이언트 지원
- 실시간 메시지 송수신
- 객체지향 설계로 유지보수 용이

## 개발 환경
- C++ 11 이상
- Linux/Unix 환경
