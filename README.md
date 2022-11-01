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

## 10월 27일  
시스템콜을 구현해야 한다.  
먼저 시스템 콜을 실행하기 전에 내가 참조하는 스택 메모리가 user모드에서 참조하는지, kernel 모드에서  
참조하는지 알아야한다. 커널에서 참조하면 exit을 해 아예 꺼준다. user 모드의 메모리는 참조해야 한다  
이에 대한 함수는 check_address() 이므로 내부 함수 is_user_vaddr()를 활용해  
현재 내가 가리키는 메모리가 가상메모리 user인지 kernel인지 판단한다.  
아직 까지는 시스템콜을 이떻게 호출되고 다시 return 하는지 전체적인 시스템을 이해하지 못하였다  
내일 다시 시작…   

## 10월 30일  
과제 제출 1일전   
일단 시스템 콜을, halt, exit, exec, write까지는 구현한 것 같다.  
근데 thread.c와 thread.h를 구현하는 방법이 아직 미숙하다.  메뉴얼을 보고 다시 수정해야 할것 같다  
echo x를 넣으면 echo Excution of 'echo x' complete 라고 뜬다.  
뭔가 파싱을 잘못했거나 한것 같다 다시 확인 해봐야 겠다  

## 10월 31일  
보니까 명령어들이 처음에 write 시스템 콜 호출하고 echo를 호출하고  
또 write 시스템 콜을 호출하고 x를 호출하는 것 같다  
따라서 syscall_handler()의 마지막에 thread_exit()을 없애고 return으로 바꿔 주면  
계속 해서 syscall을 호출할 수 있다   
역시 이렇게 바꾸니까 맞았다  
드디어 거의 다  끝났다.  
하지만 과제를 다  제 기한내에 제출하지는 못하였다.  
위에 삽질을 오래 했기 때문이다  
make check를 돌려보니  
wait-twice만 고치면 모든게 pass된다.  

## 11월 1일  
일단 프로젝트가 다 완료되었다  
어제 미완성 됐던 wait-twice는 오늘 다시 해보니까 또 된다  
make check를 돌려보니 출력 밀림 현상이 있는 것 같다  
따라서 fail이 뜬것 같다  
이제 모래 부터 userprog(2)를 시작해야 한다..  