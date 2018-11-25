// JSON simple example
// This example does not handle errors.
#include <iostream>
#include <string>
#include <fstream>
//包含rapidjson必要头文件,rapidjson文件夹拷贝到工程目录，或者设置include路径，或者加入到工程树
#include "../rapidjson/document.h"
#include "../rapidjson/filereadstream.h"
#include "../rapidjson/filewritestream.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/prettywriter.h"
#include "../rapidjson/stringbuffer.h"

#include "../rapidjson/rapidjson.h"




using namespace std;
using namespace rapidjson;  //引入rapidjson命名空间

/*
{
    "author": "tashaxing",
    "number": [
        0,
        1,
        2
    ],
    "language": {
        "language1": "C++",
        "language2": "java"
    },
    "information": [
        {
            "hobby": "drawing"
        },
        {
            "height": 1.71
        }
    ]
}
*/
/*
接口应答：

{"success":false,"code":200,"message":"操作成功","data":null}

*/
//写json文件
void json_write()
{
    Document doc;
    doc.SetObject();
    Document::AllocatorType &allocator=doc.GetAllocator(); //获取分配器
    //1.添加字符串对象
    doc.AddMember("author","tashaxing",allocator);
    //2.添加数组对象
    Value array1(kArrayType);
    for(int i=0;i<3;i++)
    {
        Value int_object(kObjectType);
        int_object.SetInt(i);
        array1.PushBack(int_object,allocator);
    }
    doc.AddMember("number",array1,allocator);
    //3.添加复合对象
    Value object(kObjectType);
    object.AddMember("language1","C++",allocator);
    object.AddMember("language2","java",allocator);
    doc.AddMember("language",object,allocator);
    //4.添加对象数组和复合对象的组合
    Value array2(kArrayType);
    Value object1(kObjectType);
    object1.AddMember("hobby","drawing",allocator);
    array2.PushBack(object1,allocator);
    Value object2(kObjectType);
    object2.AddMember("height",1.71,allocator);
    array2.PushBack(object2,allocator);
    doc.AddMember("information",array2,allocator);
    StringBuffer buffer;
    PrettyWriter<StringBuffer> pretty_writer(buffer);  //PrettyWriter是格式化的json，如果是Writer则是换行空格压缩后的json
    doc.Accept(pretty_writer);
    //打印到屏幕
    cout<<"the json output:"<<endl;
    cout<<buffer.GetString()<<endl;
    //输出到文件
    ofstream fout;
    fout.open("test");    //可以使绝对和相对路径，用\\隔开目录，test, test.json, test.txt 都行，不局限于文件格式后缀，只要是文本文档
    fout<<buffer.GetString();
    fout.close();
}

//读json文件
void json_read()
{
    cout<<"the json read:"<<endl;
    ifstream fin;
    fin.open("test");
    string str;//>16bytes 堆上分配内存
    string str_in="";
    while(getline(fin,str))    //一行一行地读到字符串str_in中
    {
        str_in=str_in+str+'\n';
    }
    //解析并打印出来
    Document document;
    document.Parse<0>(str_in.c_str());


	//document.Parse<rapidjson::kParseDefaultFlags>(str_in.c_str());
	//if (document.HasParseError() || !document.IsArray())
	//{
	//	return ;
	//}

    Value &node1=document["author"];
    cout<<"author: "<<node1.GetString()<<endl;

    Value &node2=document["number"];
    cout<<"number: "<<endl;
    if(node2.IsArray())
    {
        for(unsigned int i=0;i<node2.Size();i++)
            cout<<'\t'<<node2[i].GetInt()<<endl;
    }

    Value &node3=document["language"];
    cout<<"language: "<<endl;
    Value &tmp=node3["language1"];
    cout<<'\t'<<"language1: "<<tmp.GetString()<<endl;
    tmp=node3["language2"];
    cout<<'\t'<<"language2: "<<tmp.GetString()<<endl;

    Value &node4=document["information"];
    cout<<"information: "<<endl;
    if(node4.IsArray())
    {
        int i=0;
        Value &data=node4[i];   //注意，此处下表索引只能用变量，不能用常量，例如node[0]编译错误
        cout<<'\t'<<"hobby: "<<data["hobby"].GetString()<<endl;
        i=1;
        data=node4[i];
        cout<<'\t'<<"height: "<<data["height"].GetDouble()<<endl;
    }

}

void getJsonData(void)
{
	Document doc;
	doc.SetObject();
	Document::AllocatorType &allocator=doc.GetAllocator(); //获取分配器
	//1.添加 
	doc.AddMember("Id",1,allocator);
	//2.添加数据项
	//对象数组和复合对象的组合
	Value arrayRD(kArrayType);
#if 0	
	Value object1(kObjectType);
	object1.AddMember("dId",1,allocator);
	object1.AddMember("value",88,allocator);
	object1.AddMember("time",99,allocator);
	arrayRD.PushBack(object1,allocator);

	
	Value object2(kObjectType);
	object2.AddMember("dId",2,allocator);
	object2.AddMember("value",888,allocator);
	object2.AddMember("time",999,allocator);
	arrayRD.PushBack(object2,allocator);
#endif
	for(int i=0;i<4;i++)
	{
		Value objectItem(kObjectType);
		objectItem.AddMember("dId",1+i,allocator);
		objectItem.AddMember("value",8.8009,allocator);
		objectItem.AddMember("time",99+i,allocator);
		arrayRD.PushBack(objectItem,allocator);
	}
	doc.AddMember("datas",arrayRD,allocator);

	
	StringBuffer buffer;
	PrettyWriter<StringBuffer> pretty_writer(buffer);  //PrettyWriter是格式化的json，如果是Writer则是换行空格压缩后的json
	doc.Accept(pretty_writer);

	//打印到屏幕
	cout<<"the json output:"<<endl;
	cout<<buffer.GetString()<<endl;


}
std::string JsonToString(const rapidjson::Value& valObj)
{
    rapidjson::StringBuffer sbBuf;
    rapidjson::Writer<rapidjson::StringBuffer> jWriter(sbBuf);
    valObj.Accept(jWriter);
    return std::string(sbBuf.GetString());
}


int JsonDomTest() 
{
    // 1. Parse a JSON string into DOM.
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";

	printf("JsonDomTest:%s\r\n",json);
	Document d;
    d.Parse(json);

    // 2. Modify it by DOM.
    Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);

    // 3. Stringify the DOM
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
	printf("JsonDomTest2:%s\r\n",json);
    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;

		rapidjson::StringBuffer sbBuf;
		rapidjson::Writer<rapidjson::StringBuffer> jWriter(sbBuf);
		d.Accept(jWriter);
	 
		std::cout << sbBuf.GetString() << std::endl;


//	d.String(const Ch * str, SizeType length, bool copy)

    return 0;
}
/*
{
   "id":"000001",
   "name":"Tom",
   "urls": {
       "success_url":"http://www.success_url.com",
       "cannel_url":"http://www.cannel_url.com"
   },
   "info": {
       "desc":"description",
       "date":"2017-07-16",
       "price":{
             "amount":8.8,
             "currency":"CNY"
        }
      }
}
*/
	bool ShowJsonData1()
	{
		string filename="Json_test_1.json";
		Document doc;
		//判断文件是否存在


		//读取文件数据，初始化doc
		std::string data;
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		//判断读取成功与否 和 是否为数组类型
		if (doc.HasParseError() || !doc.IsArray())
		{
			return false;
		}
		for(unsigned int i=0;i<doc.Size();i++)
		{
			//逐个提取数组元素（声明的变量必须为引用）
			rapidjson::Value &v=doc[i];
			
			int id;//ID
			string name;//名称
			int hp;//血量
			int Defense;//防御力
			int attack;//攻击力
			int passable;//是否可穿透（通行）
			
			//判断各属性是否存在（可以支持中文（UTF8格式））
			if(v.HasMember("ID") && v.HasMember(("名称")) && v.HasMember(("血量"))
				&& v.HasMember(("防御力")) && v.HasMember(("攻击力")) && v.HasMember(("可穿透")))
			{
				//按属性提取数据
				id=v["ID"].GetInt();
				name=v[("名称")].GetString();
				hp=v[("血量")].GetInt();
				Defense=v[("防御力")].GetInt();
				attack=v[("攻击力")].GetInt();
				passable=v[("可穿透")].GetInt();
	 
                printf("json:%d%s-%d%d-%d%d",id,name.c_str(),hp,Defense,attack,passable);
			}
	 
	 
		}
		return true;
	}


void PacketJson()
{
#if 0
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    rapidjson::Value url_objects(rapidjson::kObjectType);
    rapidjson::Value price_objects(rapidjson::kObjectType);
    rapidjson::Value info_objects(rapidjson::kObjectType);
std::string data_in ;
    document.AddMember("id", rapidjson::StringRef(data_in["id"].c_str()), allocator);
    document.AddMember("name", rapidjson::StringRef(data_in["name"].c_str()), allocator);

    url_objects.AddMember("success_url", rapidjson::StringRef(data_in["success_url"].c_str()), allocator);
    url_objects.AddMember("cannel_url", rapidjson::StringRef(data_in["cannel_url"].c_str()), allocator);
    document.AddMember("urls", url_objects, allocator);

    price_objects.AddMember("amount", atof(data_in["amount"].c_str()), allocator);
    price_objects.AddMember("currency", rapidjson::StringRef(data_in["currency"].c_str()), allocator);

    info_objects.AddMember("desc", rapidjson::StringRef(data_in["desc"].c_str()), allocator);
    info_objects.AddMember("date", rapidjson::StringRef(data_in["date"].c_str()), allocator);
    info_objects.AddMember("price", price_objects, allocator);

    document.AddMember("info", info_objects, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    const std::string json = document.GetString();

    document.Accept(writer);
    //打印到屏幕
    cout<<"the json output:"<<endl;
    cout<<json<<endl;
#endif
}

/*

[
	{ 
		"bank_name" : "BOA",
    	"chain_num":123, 
    	"servers":[
    		{
    			"ip" : "127.0.0.1",
    			"port" : 1111
    		},
    		{
    			"ip" : "127.0.0.1",
    			"port" : 2222
    		}
    	] 
	},
 
	{ 
		"bank_name" : "CITIBANK",
    	"chain_num":789, 
    	"servers":[
    		{
    			"ip" : "127.0.0.1",
    			"port" : 3333
    		},
    		{
    			"ip" : "127.0.0.1",
    			"port" : 4444
    		}
    	]
	}
]
*/

int TestParseStream()
{
#if 0
    FILE *fp = fopen("t2.json", "r");
    FileStream is(fp);
 
    Document bank;
    bank.ParseStream<0>(is);
 
    if (bank.HasParseError())
    {
        printf("GetParseError %s\n", bank.GetParseError());
    }
 
    for (unsigned int i = 0; i < bank.Size(); ++i)
    {
        const Value & cur_bank = bank[i];
        cout <<"BANK # "<< i+1 <<endl;
        cout <<"bank_name: "<<cur_bank["bank_name"].GetString() << endl;
        cout <<"chain_num: " <<cur_bank["chain_num"].GetInt() << endl;
 
        Value & server_array = bank[i]["servers"];
 
        for (unsigned int j = 0; j < server_array.Size(); ++j)
        {
            cout <<"IP: "<<server_array[j]["ip"].GetString() << " ";          
            cout <<"PORT: "<<server_array[j]["port"].GetInt() << " ";
            cout <<endl;
        }
        cout <<endl;
 
    }
	#endif
    return 0;

}
string strJsonTest = "{\"item_1\":{\"sub_item_1\":\"value_1\",\"sub_item_2\":\"value_2\",\"sub_item_3\":\"value_3\"},\"item_2\":\"value_2\"}";
int jsontostring(void) 
{
	Document docTest;
	
	printf("jsontostring0:%s\r\n",strJsonTest.c_str());
	docTest.Parse<0>(strJsonTest.c_str());
	if (!docTest.HasParseError())
	{
		//if (docTest.HasMember("item_1"))
		{
			rapidjson::Value& valObj = docTest;//["item_1"];
			rapidjson::StringBuffer sbBuf;
			rapidjson::Writer<rapidjson::StringBuffer> jWriter(sbBuf);
			valObj.Accept(jWriter);
			std::string strTemp = std::string(sbBuf.GetString());
			
			printf("jsontostring1:%s\r\n",strTemp.c_str());
			//strTemp的内容为         {\"sub_item_1\":\"value_1\",\"sub_item_2\":\"value_2\",\"sub_item_3\":\"value_3\"}
		}
	}
    return 0;
}

int JsonTest()
{
    //写、读 测试
    //json_write();
    //json_read();
    JsonDomTest();
	//jsontostring();
	//getJsonData();
    return 0;
}

//
//
