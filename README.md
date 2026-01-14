프로젝트 개요

본 프로젝트는 **Qt/QML과 C++**을 기반으로 구현한
실시간 주문 처리 키오스크(POS) 애플리케이션입니다.

외부 클라이언트로부터 **TCP 통신(JSON 형식)**을 통해 주문 데이터를 수신하고,
테이블 상태 및 주문 내역을 UI에 실시간으로 반영하도록 설계되었습니다.

또한 Qt SQL 모듈을 활용한 데이터베이스 연동 구조를 구성하여,
주문 데이터의 영속적 관리가 가능하도록 확장성을 고려한 구조로 구현하였습니다.

개발 환경

OS: Windows / Qt Creator

Language: C++17

Framework: Qt 6

UI: QML / Qt Quick Controls

Build Tool: CMake

Version Control: Git / GitHub

시스템 아키텍처
[ Client ]

    ↓
TCP(JSON)

    ↓
EchoServer (QTcpServer)

    ↓
    
main.cpp (Routing)

    ↓
    
TableManager (Business Logic)

    ↓
    
QML UI (TablePage / TableDetailPage)


[ Database ]

    ↑
    
Qt SQL (Connection & Initialization)


구조 설명

* EchoServer (Network Layer) *

QTcpServer 기반 TCP 서버 구현

외부 클라이언트 연결 관리

JSON 주문 데이터 수신 및 파싱

* TableManager (Business Logic)

테이블 상태 및 주문 데이터 중앙 관리

주문 추가 / 테이블 초기화 처리

UI와 완전히 분리된 로직 계층

* QML UI (Presentation Layer)

StackView 기반 화면 전환

테이블 현황 화면 / 주문 상세 화면 구성

C++ 로직과 Q_PROPERTY 바인딩을 통한 실시간 갱신

* Database Layer

Qt SQL 모듈을 통한 DB 연결 및 초기화

DB 연결 실패 시 애플리케이션 실행 중단

주문 데이터 저장을 고려한 확장 구조 설계

 주요 구현 기능
1️ TCP 기반 실시간 주문 처리

외부 클라이언트와 TCP 연결

JSON 형식 주문 데이터 파싱 및 검증

주문 수신 즉시 테이블 상태 반영

2️ 비즈니스 로직 중앙 관리

TableManager를 통한 상태 일관성 유지

UI는 데이터 표현만 담당

유지보수 및 기능 확장에 유리한 구조

3️ QML–C++ 데이터 바인딩

Q_PROPERTY 기반 데이터 바인딩

서버 주문 → UI 자동 반영

4️ 데이터베이스 연동 구조

애플리케이션 시작 시 DB 연결 초기화

DB 연동 실패 시 예외 처리

데이터 영속성 확장을 고려한 설계

테스트 방법
서버 실행

애플리케이션 실행 후 서버를 활성화합니다.

주문 테스트 (PowerShell)
$client = New-Object System.Net.Sockets.TcpClient("127.0.0.1", 8080)
$stream = $client.GetStream()

$msg = '{"type":"order","tableId":1,"menu":"아메리카노","quantity":2,"price":8000}'
$bytes = [System.Text.Encoding]::UTF8.GetBytes($msg)

$stream.Write($bytes, 0, $bytes.Length)
$stream.Close()
$client.Close()

결과

테이블 화면에서 해당 테이블의 금액 즉시 표시

상세 페이지에서 주문 목록 실시간 갱신
