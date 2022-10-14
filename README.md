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

## 10월 14일  
스택을 드디어 다 쌓았다  
어제 쓰레기 값이 들어간 부분은 내가 디버깅용 출력을 했을 때  
%d로 찍었기 때문이다.  
다시 포인터로 찍기 위해 %p로 찍었지만 여전히 paging fault가 나왔다.  
구글링과 디버깅을 통해 내가 주소값을 넣을 스택에 말 그대로 argv의 주소값이 들어간 것이다.  
argv를 저장한 스택의 주소값을 넣어야 하지만 나는 그렇지 않았기 때문에 오류가 나온것이었다.  
그래서 처음 스택 쌓을 때 argv의 data값이 들어가는 for문에  미리 해당 esp의 주소값을 따로 저장해 두어  
나중에 주소값을 넣을 때 사용하게 하였다.  
그렇게 해서 system call! 이라는 문구가 터미널에 나왔다.  
내일 부터는 system call부분을 작업할 것이다.