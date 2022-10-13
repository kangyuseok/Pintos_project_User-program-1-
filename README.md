# Pintos_project_User-program-1-
sogang univ - os - pintos proj


## 10월 11일   
디버깅용 printf가 안찍힘  

## 10월 12일    
알고 보니 계속 컴파일을 하지 않아서 실행파일에 반영이 되지 않은 것이었다.  
컴파일을 하려면 src/userprog/build로 들어가 make 명령어를 치고. 
cd .. 명령어를 통해 다시 src/userprog로 돌아와   
pintos --filesys-size=2 -p ../examples/echo -a echo -- -f -q run 'echo x'  
를 입력하면 된다.  
일단 현재 load() 에서 argument parsing 까지 완료하였다.  
내일 부터는 argument parsing 된것을 stack에 쌓아야 한다.  

## 10월 13일
스택을 쌓고 있는 와중에 어려움을 겪었다  
차례대로 잘 쌓아지다가 argv[0], argv[1], argv 의 주소값을 넣는 과정에서 쓰레기 값이 계속 스택에 쌓인다.   
나머지 부분은 잘 들어가는 것 같지만 좀더 데이터 타입 이든지 void 형 포인터 든지 좀더 연구를 해야할 것 같다   

