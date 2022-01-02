/*****************************************************************************
**
** NX10_Open_QuickSignature.c
**
** Description:
**     The quick signature plug-in for engineering drawings, based on the API interface of UG secondary development.
**
**
**This codes had been written by Zhizhen Dong in 2020-2021
**
*****************************************************************************/

/* Include files */
#include <stdarg.h>
#include <stdio.h>
#include <uf.h>
#include <uf_ui.h>
#include <uf_ui_types.h>
#include <uf_modl.h>
#include <uf_curve.h>
#include <uf_drf.h>
#include <uf_draw.h>
#include <uf_part.h>
#include <string.h>
#include <time.h>

static void ECHO(char *format, ...)
{
    char msg[UF_UI_MAX_STRING_NCHARS+1];
    va_list args;
    va_start(args, format);
    vsnprintf_s(msg, sizeof(msg), UF_UI_MAX_STRING_NCHARS, format, args);
    va_end(args);
    UF_UI_open_listing_window();
    UF_UI_write_listing_window(msg);
    UF_print_syslog(msg, FALSE);
}

#define UF_CALL(X) (report_error( __FILE__, __LINE__, #X, (X)))

static int report_error( char *file, int line, char *call, int irc)
{
    if (irc)
    {
        char err[133];

        UF_get_fail_message(irc, err);
        ECHO("*** ERROR code %d at line %d in %s:\n",
            irc, line, file);
        ECHO("+++ %s\n", err);
        ECHO("%s;\n", call);
    }

    return(irc);
}

void Pointer_stringcat(char *str1, const char *str2)//C语言:通过指针对字符串进行拼接
{
	while (*(str1++) != '\0');     //一直将指向str1的指针移到字符串的末尾
	str1--;
	while (*str2 != '\0')
	{
		*(str1++) = *(str2++);  //开始连接
	}
	*str1 = '\0';               //连接完后,添加上字符串结束标识符
}

/*****************************************************************************
**  Activation Methods
*****************************************************************************/
/*  Explicit Activation
**      This entry point is used to activate the application explicitly, as in
**      "File->Execute UG/Open->User Function..." */
extern DllExport void ufusr( char *parm, int *returnCode, int rlen )
{
    /* Initialize the API environment */
    if( UF_CALL(UF_initialize()) ) 
    {
        /* Failed to initialize */
		
        return;
    }
    
    /* TODO: Add your application code here */


	char* inspath;
	UF_translate_variable("UGII_BASE_DIR", &inspath); //UGII路径
														  //电子表格模板路径
	char* SignDIR = inspath;		                  //const char* BaseDIR1 = translation;        //这个是一个字符串常量,不能更改字符串的值
	char* SignDIR1 = "\\LOCALIZATION\\signtool";         //这个是一个字符串常量,不能更改字符串的值
	char file_temp[200];                  //这个是一个字符串变量,字符串的值可以被修改
	char file_path[200];                  //这个是一个字符串变量,字符串的值可以被修改
	strcpy(file_temp, SignDIR);
	Pointer_stringcat(file_temp, SignDIR1);

	//单选菜单对话框
	char sPromptStr[] = "单选菜单对话框";
	int iDefault = 0;//表示没有默认选项,OK按钮始终保持不激活状态
	char asOptions[][38] = { "快速签名", "日期填写" };
	int iNumOfOtions = 2;//最多包含14个菜单选项
	int value = uc1603(sPromptStr, iDefault, asOptions, iNumOfOtions);

	if (value == 5)//启动快速签名
	{

		UF_DRAW_info_t drawing_info;
		tag_t DrawingTag = NULL_TAG;
		//drawing_info.size;
		UF_DRAW_ask_drawing_info(DrawingTag, &drawing_info);
		int ws = drawing_info.size.custom_size[1]; //查询图纸宽度

		if (ws == 210)   //A4
		{
			//插入PNG
			char* SignDIR2 = "\\1.png";
			strcpy(file_path,file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			double origin[3] = { 48.0, 22.5, 0.0 };
			tag_t ImageTag = NULL_TAG;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);


			//插入PNG
			SignDIR2 = "\\2.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 17.5;

			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			//插入PNG
			SignDIR2 = "\\3.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 12.5;

			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\4.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 7.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\5.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[0] = 76.5;
			origin[1] = 22.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\6.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 17.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\7.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 12.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			uc1601("导入成功", 1);
		}
		else if (ws == 420)   //A3
		{
			//插入PNG
			char* SignDIR2 = "\\1.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			double origin[3] = { 258.0, 22.5, 0.0 };
			tag_t ImageTag = NULL_TAG;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);


			//插入PNG
			SignDIR2 = "\\2.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 17.5;

			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			//插入PNG
			SignDIR2 = "\\3.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 12.5;

			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\4.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 7.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\5.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[0] = 286.5;
			origin[1] = 22.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\6.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 17.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\7.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 12.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);


			uc1601("导入成功", 1);
		}
		else if (ws == 594)   //A2
		{
			//插入PNG
			char* SignDIR2 = "\\1.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			double origin[3] = { 427.0, 27.5, 0.0 };
			tag_t ImageTag = NULL_TAG;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);


			//插入PNG
			SignDIR2 = "\\2.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 22.5;

			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			//插入PNG
			SignDIR2 = "\\3.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 17.5;

			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\4.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 12.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\5.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[0] = 455.5;
			origin[1] = 27.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\6.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 22.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\7.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 17.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			uc1601("导入成功", 1);
		}
		else if (ws == 841)   //A1
		{
			//插入PNG
			char* SignDIR2 = "\\1.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			double origin[3] = { 674.0, 27.5, 0.0 };
			tag_t ImageTag = NULL_TAG;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);


			//插入PNG
			SignDIR2 = "\\2.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 22.5;

			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			//插入PNG
			SignDIR2 = "\\3.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 17.5;

			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\4.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 12.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\5.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[0] = 702.5;
			origin[1] = 27.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\6.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 22.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\7.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 17.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			uc1601("导入成功", 1);
		}
		else if (ws == 1189)   //A0
		{
			//插入PNG
			char* SignDIR2 = "\\1.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			double origin[3] = { 1022.0, 27.5, 0.0 };
			tag_t ImageTag = NULL_TAG;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);


			//插入PNG
			SignDIR2 = "\\2.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 22.5;

			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			//插入PNG
			SignDIR2 = "\\3.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 17.5;

			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\4.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 12.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\5.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[0] = 1050.5;
			origin[1] = 27.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\6.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 22.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\7.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 17.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			uc1601("导入成功", 1);
		}
		else if (ws == 1635)   //A0+
		{
			//插入PNG
			char* SignDIR2 = "\\1.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			double origin[3] = { 1468.0, 27.5, 0.0 };
			tag_t ImageTag = NULL_TAG;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);


			//插入PNG
			SignDIR2 = "\\2.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 22.5;

			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			//插入PNG
			SignDIR2 = "\\3.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 17.5;

			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\4.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 12.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\5.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[0] = 1496.5;
			origin[1] = 27.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\6.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 22.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\7.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 17.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			uc1601("导入成功", 1);
		}
		else if (ws == 2387)   //A0++
		{
			//插入PNG
			char* SignDIR2 = "\\1.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			double origin[3] = { 2220.0, 27.5, 0.0 };
			tag_t ImageTag = NULL_TAG;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);


			//插入PNG
			SignDIR2 = "\\2.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 22.5;

			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			//插入PNG
			SignDIR2 = "\\3.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 17.5;

			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\4.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 12.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\5.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[0] = 2248.5;
			origin[1] = 27.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\6.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 22.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			SignDIR2 = "\\7.png";
			strcpy(file_path, file_temp);
			Pointer_stringcat(file_path, SignDIR2);

			origin[1] = 17.5;
			UF_DRF_create_image_from_file(file_path, NULL_TAG, origin, &ImageTag);

			//设置图片高度
			UF_DRF_set_image_height(ImageTag, 5);

			uc1601("张专家加戏啊", 1);
		}
		else
		{
			uc1601("无法识别图框，导入失败", 1);
		}

		//保存part
		UF_PART_save();

	}//结束快速签名

	if (value == 6)//开始日期填写
	{
		uc1601("开发中……", 1);

	}//结束日期填写

	/* Terminate the API environment */
	UF_CALL(UF_terminate());
}

/*****************************************************************************
**  Utilities
*****************************************************************************/

/* Unload Handler
**     This function specifies when to unload your application from Unigraphics.
**     If your application registers a callback (from a MenuScript item or a
**     User Defined Object for example), this function MUST return
**     "UF_UNLOAD_UG_TERMINATE". */
extern int ufusr_ask_unload( void )
{
    return( UF_UNLOAD_IMMEDIATELY );
}

