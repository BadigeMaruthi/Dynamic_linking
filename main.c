#include<stdio.h>
#include<dlfcn.h>
#include"calc.h"

void Dynamic_run(char*,int,int);

void main()
{
	int a,b,op;
	char *cal[]={"sum","sub","mul","div"};
	printf("Enter two numbers:");
	scanf("%d%d",&a,&b);
	printf("1.sum 2.sub 3.mul 4.div\n");
	scanf("%d",&op);
	if(op>=1 && op<=4)
               Dynamic_run(cal[op-1],a,b);
	else
	   printf("Invalid choice...\n");

	return;
}

void Dynamic_run(char *str,int a,int b)
{
	void *handler;
	int(*p)(int,int);
	handler = dlopen("./libcal.so",RTLD_LAZY);
	if(handler==NULL)
	{
		printf("%s\n",dlerror());
		return;
	}
	p=(int(*)(int,int))dlsym(handler,str);
	if(p==NULL)
	{
		printf("%s\n",dlerror());
		dlclose(handler);
		return;
	}
	printf("Result=%d\n",p(a,b));
	dlclose(handler);
}
