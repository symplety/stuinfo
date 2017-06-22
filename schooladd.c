#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"
char * head = "head.html";
char * foot= "footer.html";

int cgiMain()
{
  FILE * fd;
	 char ch;
	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
	fd=fopen("head.html", "r");
	if(fd==NULL){
			fprintf(cgiOut, "Cannot open file,head.html \n");
			return -1;
		}
		ch = fgetc(fd);

		while(ch != EOF){
			fprintf(cgiOut, "%c", ch);
			ch = fgetc(fd);
		}
	fclose(fd);
fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
	char scid[5] = "\0";
	char scname[20] = "\0";
	int status = 0;

	status = cgiFormString("scid",  scid, 5);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get scid error!\n");
		return 1;
	}

	status = cgiFormString("scname",  scname, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get scname error!\n");
		return 1;
	}



	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

//	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);

	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "1", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

/*	strcpy(sql, "create table information(id char(15) not null primary key, name char(20) not null, scid char(10),age int(11)check(age between 1 and 150),grade int(11) check(grade between 1 and 6,sex char(10) check(sex in("男",“女”),foreign key(scid) references(school)
)");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}

*/


		sprintf(sql, "insert into school values('%s','%s')", scid, scname);
		if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
		{
			fprintf(cgiOut, "%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}



	fprintf(cgiOut, "add school ok!\n");
	mysql_close(db);
	return 0;
}
