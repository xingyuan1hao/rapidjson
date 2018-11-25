	
	//组包json数组对象
	string com::PackJsonData(void)
	{
		int id = 0;
		int ret = -1;
		int dId=0;// 
		int cType=0;// 
		double data=0;// 
		unsigned int spotTime=0;//时间点
		char *buf;

		Document doc;
		doc.SetArray();        //数组型 相当与vector
		Document::AllocatorType &allocator=doc.GetAllocator(); //获取分配器

		//Value objectMeters(kArrayType);
		//
		for (int i=0; i<2; i++)
		{
			//1.添加id
			Value objmeter(kObjectType);
			objmeter.SetObject();
			objmeter.AddMember("Id",id+i,allocator);
			//2.添加数据项
			//对象数组和复合对象的组合
			Value arrayRD(kArrayType);
			for(int j=0; j<2; j++)
			{
				Value objectItem(kObjectType);
				objectItem.AddMember("dId",dId+j,allocator);
				objectItem.AddMember("value",data+j,allocator);
				objectItem.AddMember("time",spotTime+j,allocator);
				arrayRD.PushBack(objectItem,allocator);
			}
			objmeter.AddMember("ds",arrayRD,allocator);
			//objectMeters.PushBack(objmeter,allocator);
			
			doc.PushBack(objmeter,allocator);
		}
		
		StringBuffer buffer;
		PrettyWriter<StringBuffer> pretty_writer(buffer);  //PrettyWriter是格式化的json，如果是Writer则是换行空格压缩后的json
		doc.Accept(pretty_writer);
				
		//打印到屏幕
		cout<<"the PackRecordJsonData output:"<<endl;
		cout<<buffer.GetString()<<endl;

		return buffer.GetString();
	}
	