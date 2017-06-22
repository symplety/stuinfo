#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "cgic.h"
char * head = "head.html";
char * foot= "footer.html";

int cgiMain()
{
	FILE * fd;
	 char ch;
	fprintf(cgiOut, "\n\n");
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
	fprintf(cgiOut, "\n\n");
	fprintf(cgiOut, "<head><meta charset=\"utf-8\"><title>查询结果</title>\
		    <link rel=\"stylesheet\" href=\"/stu/public/css/bootstrap.min.css\">\
		</head>");

	char id[15] = "\0";
	int status = 0;

	status = cgiFormString("id",  id, 15);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get id error!\n");
		return 1;
	}

	int ret;
	MYSQL *db;
	char sql[128] = "\0";

	if (id[0] == '*')
	{
		sprintf(sql, "select * from sc");
//    fprintf(cgiOut, "select * from sc\n");
    fprintf(cgiOut, "<div class=\"container\"> <h1 class=\"text-center\">查所有学生成绩</h1>");

	}
	else
	{
		sprintf(sql, "select * from sc where id = '%s'", id[0]);
    fprintf(cgiOut, "<div class=\"container\"> <h1 class=\"text-center\">%s学生成绩</h1>",id);

	}


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


	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	MYSQL_RES *res;
	res = mysql_store_result(db);
	if (res == NULL)
	{
		fprintf(cgiOut,"mysql_store_result fail:%s\n", mysql_error(db));
		return -1;
	}


	fprintf(cgiOut,"<table class=\"table table-striped table-bordered\"><tr>");
	int i = 0;

	unsigned int fields;
	fields = mysql_num_fields(res);//返回mysql_store_result的记录个数

	MYSQL_FIELD *mysql_filed;
	mysql_filed = mysql_fetch_fields(res);//返回集合中列的定义（即获取每列的属性名）
	for (i = 0; i < fields ; i++)
	{
		fprintf(cgiOut, "<th>%s</th>", mysql_filed[i].name);
	}
	fprintf(cgiOut,"</tr>");

	//访问每一条记录的值
	MYSQL_ROW  row;
	unsigned long  *len;

	while ((row = mysql_fetch_row(res)) != NULL)//返回集合中的一行
	{
		fprintf(cgiOut,"<tr>");
		len = mysql_fetch_lengths(res);//返回当前行中每一个字段值的长度
		for (i = 0; i < fields ; i++)
		{
			fprintf(cgiOut,"<td>%.*s</td>", (int)len[i], row[i]);
		}
		fprintf(cgiOut,"</tr>");
	}
	fprintf(cgiOut,"</table></div>");



	mysql_close(db);
	return 0;
}
