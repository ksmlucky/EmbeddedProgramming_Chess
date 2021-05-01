# EmbeddedProgramming_Chess
라즈베리파이(Raspberry Pi)를 이용하는 체스게임(Qt로 UI를 구현)
-----

- 라즈베리파이 2대를 사용하여 플레이하는 체스 게임으로 TCP 소켓을 사용하여 구현하였다.      
      
- 한 대는 서버, 다른 한 대는 클라이언트로 플레이한다.     
(Chess-master가 서버, ChessClient가 클라이언트)

#### 게임 시작 화면
![image](https://user-images.githubusercontent.com/77111523/116769928-c1dab500-aa7a-11eb-8e4c-be5835c5a3e1.png)

Connect 버튼 --> 소켓 연결     Quit 버튼 --> 종료

#### 게임 플레이 화면
![image](https://user-images.githubusercontent.com/77111523/116770050-b20fa080-aa7b-11eb-9994-2d893d058931.png)

기물을 클릭하면 선택된 기물이 있는 칸의 색이 변하면 이동가능한 경로가 표시된다.     
     

![image](https://user-images.githubusercontent.com/77111523/116770149-7e814600-aa7c-11eb-8e79-a9b5c713a49e.png)

이동할 경우 상대편에게 이동한 움직인 기물에 대한 정보가 전달된다.     
     

![image](https://user-images.githubusercontent.com/77111523/116770163-9f499b80-aa7c-11eb-886b-e36d364dfa20.png)

이동 가능 경로에 상대편 기물이 있을 경우, 그 칸은 같은 빨간색으로 표시된다.     
     

![image](https://user-images.githubusercontent.com/77111523/116770190-ab355d80-aa7c-11eb-9b47-16faf60abe78.png)

상대편의 말을 잡았을 경우, 잡힌 말의 색에 따라 왼쪽, 오른쪽 공간에 위치하게 된다.

     
