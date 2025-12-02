# TCP/IP Socket Communication Program

## 프로젝트 소개
C++로 구현한 TCP/IP 소켓 통신 채팅 프로그램입니다.
객체지향 설계 원칙을 적용하여 각 기능을 독립적인 클래스로 분리하였으며,
헤더 파일과 구현 파일을 명확히 구분하여 유지보수가 용이합니다.

## 프로젝트 구조
```
Socket_Chating_Program/
├── include/          # 헤더 파일
│   ├── Server.h      # 서버 클래스 선언
│   ├── Client.h      # 클라이언트 클래스 선언
│   └── MessageHandler.h  # 메시지 처리 유틸리티
├── src/             # 구현 파일
│   ├── Server.cpp    # 서버 클래스 구현
│   ├── Client.cpp    # 클라이언트 클래스 구현
│   └── MessageHandler.cpp  # 메시지 처리 유틸리티 구현
├── server_main.cpp  # 서버 메인 프로그램
├── client_main.cpp  # 클라이언트 메인 프로그램
├── Makefile        # 빌드 스크립트
└── README.md       # 프로젝트 문서
```

## 주요 클래스 설명

### 1. Server 클래스 (Server.h/cpp)
- **기능**: TCP 서버 소켓 관리 및 멀티 클라이언트 처리
- **주요 메서드**:
  - `start()`: 서버 시작 및 클라이언트 연결 대기
  - `stop()`: 서버 종료 및 리소스 정리
  - `broadcastMessage()`: 모든 클라이언트에게 메시지 브로드캐스트
  - `handleClient()`: 개별 클라이언트 연결 처리 (멀티쓰레드)

### 2. Client 클래스 (Client.h/cpp)
- **기능**: TCP 클라이언트 소켓 관리 및 서버 통신
- **주요 메서드**:
  - `start()`: 서버 연결 시작
  - `sendMessage()`: 서버에 메시지 전송
  - `receiveMessages()`: 서버로부터 메시지 수신 (비동기)
  - `disconnect()`: 서버 연결 종료

### 3. MessageHandler 클래스 (MessageHandler.h/cpp)
- **기능**: 메시지 검증 및 포맷팅 유틸리티
- **주요 메서드**:
  - `formatMessage()`: 타임스탬프와 발신자 정보 추가
  - `getCurrentTimestamp()`: 현재 시각 문자열 반환
  - `isValidMessage()`: 메시지 유효성 검증
  - `trimMessage()`: 메시지 공백 제거

## 빌드 및 실행 방법

### 빌드
```bash
# 전체 빌드 (서버 + 클라이언트)
make

# 서버만 빌드
make server

# 클라이언트만 빌드
make client

# 빌드 파일 정리
make clean

# 재빌드
make rebuild
```

### 실행

#### 서버 실행
```bash
# 기본 포트(8080)로 실행
./server

# 사용자 지정 포트로 실행
./server 9999
```

#### 클라이언트 실행
```bash
# 로컬호스트 기본 포트(8080)로 연결
./client

# 사용자 지정 IP와 포트로 연결
./client 192.168.1.100 9999

# 종료: 'quit' 또는 'exit' 입력, 또는 Ctrl+C
```

## 주요 기능

### 서버 기능
- ✅ TCP 소켓 생성 및 바인딩
- ✅ 멀티 클라이언트 동시 연결 지원 (std::thread 활용)
- ✅ 클라이언트 간 메시지 브로드캐스팅
- ✅ 클라이언트 연결/해제 감지 및 관리
- ✅ 우아한 종료 처리 (SIGINT, SIGTERM)

### 클라이언트 기능
- ✅ 서버 연결 및 인증
- ✅ 실시간 메시지 송수신
- ✅ 비동기 메시지 수신 (별도 쓰레드)
- ✅ 메시지 유효성 검증
- ✅ 우아한 연결 종료

### 설계 특징
- ✅ 객체지향 프로그래밍 (OOP) 원칙 적용
- ✅ 헤더/구현 파일 분리로 인터페이스 명확화
- ✅ RAII 패턴을 통한 리소스 관리
- ✅ 멀티쓰레딩으로 동시성 처리
- ✅ 에러 처리 및 예외 안전성

## 기술 스택
- **언어**: C++11
- **네트워크**: POSIX Socket API (TCP/IP)
- **동시성**: std::thread (C++11 표준 라이브러리)
- **빌드 도구**: GNU Make
- **플랫폼**: Linux/Unix

## 개발 환경
- C++ 11 이상
- GCC/G++ 컴파일러
- Linux/Unix 환경 (POSIX 호환)
- pthread 라이브러리

## 테스트 방법

### 1. 로컬 테스트
```bash
# 터미널 1: 서버 실행
./server

# 터미널 2: 클라이언트 1 실행
./client

# 터미널 3: 클라이언트 2 실행
./client
```

### 2. 네트워크 테스트
```bash
# 서버 (192.168.1.100)
./server 8080

# 클라이언트 (다른 컴퓨터에서)
./client 192.168.1.100 8080
```

## 학습 목표
이 프로젝트를 통해 다음을 학습할 수 있습니다:
- TCP/IP 소켓 프로그래밍 기초
- 멀티쓰레드 프로그래밍
- 클라이언트-서버 아키텍처
- 객체지향 설계 및 구현
- C++ 프로젝트 구조화 및 빌드 시스템
