/*
	本程序所实现的功能为 【**.exe srcFile  desFile】 ,就是将srcFile 拷贝一份到desfile，
	所以在运行程序时必须在后面添加两个参数，第一个是已经存在的文件的路径，另一个是需要
	复制到的路径。
	本程序主要是利用文件操作函数中的 fgetc() 函数 与 fputc() 函数。

	函数说明：
		fgetc(FILE *fp):
			从流中读取一个字符，同时没取完一个字符fp 指针会自动指向下一个字符。
			当读取错误时会返回EOF。可以通过返回值判断当前文件是否读完。
		fputc(char ch, FILE *fp):
			向流中输入一个字符，与fgetc 相似，在每写入一个后fp 指向下一个，等待继续输入，或者
			流关闭

	在函数中我们还需要用到 fopen(char * fileName, char *type),第一个参数就是我们所需要的文件路径，
	第二个参数就是读取的方式。读取方式如下：
		r:只读方式打开一个文本，只允许读数据
		w:只写打开或建立一个文本文件，只允许写数据
		a:追加打开一个文本文件，并在文件末尾写数据
		rb:只读打开一个二进制文件，只读
		wb:只写打开，或建立一个二进制文件，只允许写数据
		ab:追加打开一个二进制文件，并在文件末尾写数据
		r+:读写打开一个文本文件，允许写和读
		w+:读写打开或建立一个文本文件，可以读和写
		a+:读写打开一个文本文件，允许读，或在文件末尾追加数据
		rb+:读写打开一个二进制文件，允许读和写
		wb+:读写打开或建立一个二进制文件，允许读和写
		ab+:读写打开一个二进制文件，允许读，或在文件末尾追加数据
	还有第二个函数fclose(FILE *fp) ,也就是关闭文件流，这个很重要
	
	后面添加：
		函数原型： int access(const char *filename, int mode);

		所属头文件：#include <io.h>
		filename：可以填写文件夹路径或者文件路径

		mode： 0 （F_OK） 只判断是否存在

	           2 （R_OK） 判断写入权限

	           4 （W_OK） 判断读取权限

	           6 （X_OK） 判断执行权限

	    在这个程序中我们只使用用F_OK 文件是否存在

*/
#include<io.h>// 在这个头文件中包含有检测当前文件是否存在的函数access(const char *filename, int mode);
#include<stdio.h>// 在这个头文件中包含了我们所需要的各个文件操作函数
int main(int argc, char* argv[])
{
	FILE *srcFile , *desFile;//定义两个文件指针
	if(argc != 3)// 判断参数输入是否满足要求
	{
		printf("Please input <%s srcFile desFile>",argv[0]);// 这个地方提示用户程序执行的正确方式
		return 0;
	}
	srcFile = fopen(argv[1],"rb");//以读取二进制的方式打开源文件
	if(srcFile == NULL)
	{
		printf("Source file open failure!!");
		printf("Press any key to close!!");
		getchar();
		return 0;
	}

	if ( !access(argv[2],0) )
	{
		printf("%s EXISITS!!",argv[2]);
		printf("Source file open failure!!");
		printf("Press any key to close!!");
		getchar();
		return 0;
	}

	desFile = fopen(argv[2],"wb");//以写入二进制方式打开目标文件
	if(desFile == NULL)
	{
		printf("Destination file open failure!!");
		printf("Press any key to close!!");
		getchar();
        return 0;
	}
	  /* start copy */
    while(!feof(srcFile))// 判断当前指针的指向是否为EOF
    {
        putc(getc(srcFile),desFile);
    }

    fclose(srcFile);
    fclose(desFile);

	return 0;
}

/* 这个程序如果想要更加的人性话，可以在用户运行函数后，输入源文件和目标文件，同时还应具备
	检查目标文件是否存在的问题，不然在复制文件时，可能导致其他文件受损。
*/

// 已经加入判断文件是否存在