/*
	��������ʵ�ֵĹ���Ϊ ��**.exe srcFile  desFile�� ,���ǽ�srcFile ����һ�ݵ�desfile��
	���������г���ʱ�����ں������������������һ�����Ѿ����ڵ��ļ���·������һ������Ҫ
	���Ƶ���·����
	��������Ҫ�������ļ����������е� fgetc() ���� �� fputc() ������

	����˵����
		fgetc(FILE *fp):
			�����ж�ȡһ���ַ���ͬʱûȡ��һ���ַ�fp ָ����Զ�ָ����һ���ַ���
			����ȡ����ʱ�᷵��EOF������ͨ������ֵ�жϵ�ǰ�ļ��Ƿ���ꡣ
		fputc(char ch, FILE *fp):
			����������һ���ַ�����fgetc ���ƣ���ÿд��һ����fp ָ����һ�����ȴ��������룬����
			���ر�

	�ں��������ǻ���Ҫ�õ� fopen(char * fileName, char *type),��һ������������������Ҫ���ļ�·����
	�ڶ����������Ƕ�ȡ�ķ�ʽ����ȡ��ʽ���£�
		r:ֻ����ʽ��һ���ı���ֻ���������
		w:ֻд�򿪻���һ���ı��ļ���ֻ����д����
		a:׷�Ӵ�һ���ı��ļ��������ļ�ĩβд����
		rb:ֻ����һ���������ļ���ֻ��
		wb:ֻд�򿪣�����һ���������ļ���ֻ����д����
		ab:׷�Ӵ�һ���������ļ��������ļ�ĩβд����
		r+:��д��һ���ı��ļ�������д�Ͷ�
		w+:��д�򿪻���һ���ı��ļ������Զ���д
		a+:��д��һ���ı��ļ���������������ļ�ĩβ׷������
		rb+:��д��һ���������ļ����������д
		wb+:��д�򿪻���һ���������ļ����������д
		ab+:��д��һ���������ļ���������������ļ�ĩβ׷������
	���еڶ�������fclose(FILE *fp) ,Ҳ���ǹر��ļ������������Ҫ
	
	������ӣ�
		����ԭ�ͣ� int access(const char *filename, int mode);

		����ͷ�ļ���#include <io.h>
		filename��������д�ļ���·�������ļ�·��

		mode�� 0 ��F_OK�� ֻ�ж��Ƿ����

	           2 ��R_OK�� �ж�д��Ȩ��

	           4 ��W_OK�� �ж϶�ȡȨ��

	           6 ��X_OK�� �ж�ִ��Ȩ��

	    ���������������ֻʹ����F_OK �ļ��Ƿ����

*/
#include<io.h>// �����ͷ�ļ��а����м�⵱ǰ�ļ��Ƿ���ڵĺ���access(const char *filename, int mode);
#include<stdio.h>// �����ͷ�ļ��а�������������Ҫ�ĸ����ļ���������
int main(int argc, char* argv[])
{
	FILE *srcFile , *desFile;//���������ļ�ָ��
	if(argc != 3)// �жϲ��������Ƿ�����Ҫ��
	{
		printf("Please input <%s srcFile desFile>",argv[0]);// ����ط���ʾ�û�����ִ�е���ȷ��ʽ
		return 0;
	}
	srcFile = fopen(argv[1],"rb");//�Զ�ȡ�����Ƶķ�ʽ��Դ�ļ�
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

	desFile = fopen(argv[2],"wb");//��д������Ʒ�ʽ��Ŀ���ļ�
	if(desFile == NULL)
	{
		printf("Destination file open failure!!");
		printf("Press any key to close!!");
		getchar();
        return 0;
	}
	  /* start copy */
    while(!feof(srcFile))// �жϵ�ǰָ���ָ���Ƿ�ΪEOF
    {
        putc(getc(srcFile),desFile);
    }

    fclose(srcFile);
    fclose(desFile);

	return 0;
}

/* ������������Ҫ���ӵ����Ի����������û����к���������Դ�ļ���Ŀ���ļ���ͬʱ��Ӧ�߱�
	���Ŀ���ļ��Ƿ���ڵ����⣬��Ȼ�ڸ����ļ�ʱ�����ܵ��������ļ�����
*/

// �Ѿ������ж��ļ��Ƿ����