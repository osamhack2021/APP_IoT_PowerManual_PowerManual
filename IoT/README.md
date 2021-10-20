 작동순서:  
1. 전원 버튼을 이용하여 디바이스의 전원을 on/off  
2. 전원 LED가 on이 되었음을 알려줌  
3. 블루투스 연결이 자동으로 시작
4. 연결되기 전에는 블루투스모듈의 LED가 깜빡이다가 페어링이 되면 켜진 상태 유지
5. 이후 앱에서 디바이스를 조종하게 됨
6. 운동중이 아닐때는 아두이노의 led가 파란색으로 깜빡거림
7. 앱에서 운동과 횟수를 고르고 운동 시작을 누르면 디바이스가 해당 운동 준비를 시작
8. 운동 상태 LED가 노란불로 시작하여 시작자세를 잡으면 초록불로 변하고 2초후 운동이 시작됨
9. 설정해놓은 횟수가 끝나면 각 횟수마다 잘못되었던 자세 log를 보여주고 그에 따라 점수를 매김

운동 자세 측정 알고리즘:  
1. 스쿼트:  
기본 자세:  
적절하게 다리를 벌리고 서있는 자세에서 시작  
운동 자세:  
다리 각도 유지, 양 무릎은 발 앞까지만, 허벅지는 바닥과 평행한 높이까지 내리고 올라오기, 적당한 속도  

측정 자세:   
1. 허벅지가 바닥과 평행을 이루고 올라오는지  
2. 속도는 적당한지  

동작 구분:  
1. 내려가는 동작  
2. 올라오는 동작  

판단 종류:  
1. 충분히 내려가지 않음  
2. 너무 내려감    
3. 너무 빨리 내려감  
4. 너무 빨리 올라옴  
5. 올바른 자세  

판단 원리:  
실험으로 얻은 데이터를 통해 각 구분 동작마다 기준이 되는 값들을 선정하여 그 값들의 오차범위에 포함되는 측정값들을 올바른 자세로 판단

시연 구성:
1. 전원스위치, 전원 LED, 운동상태 LED: https://www.tinkercad.com/things/6TsqGjZfOjW
2. 가속도센서와 운동상태 LED: 
3. 스쿼트시연


