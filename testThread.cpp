#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mMutex;
mutex pMutex;

void print(int num){
	pMutex.lock();
	cout<<"Thread1 No."<<num-1<<endl;
	pMutex.unlock();
}

void test(int num){
	mMutex.lock();
	int sum = 0;
	for(int i=0;i<num;i++)
		sum+=i;
	cout<<"Thread No."<<num-1<<endl;
	cout<<"sum: "<<sum<<endl;
	mMutex.unlock();
	print(num);
}

int main( int argc, char** argv ){
	thread threadArr[10];
	
	for(int i=1;i<=10;i++){
		if(i<5)
			threadArr[i-1] = thread(test, i);
		else
			threadArr[i-1] = thread(print, i);
	}
	for(int i=1;i<=10;i++){
		threadArr[i-1].join();
	}
	cout<<"Done."<<endl;
	return 0;
}
