	
	//���json�������
	string com::PackJsonData(void)
	{
		int id = 0;
		int ret = -1;
		int dId=0;// 
		int cType=0;// 
		double data=0;// 
		unsigned int spotTime=0;//ʱ���
		char *buf;

		Document doc;
		doc.SetArray();        //������ �൱��vector
		Document::AllocatorType &allocator=doc.GetAllocator(); //��ȡ������

		//Value objectMeters(kArrayType);
		//
		for (int i=0; i<2; i++)
		{
			//1.���id
			Value objmeter(kObjectType);
			objmeter.SetObject();
			objmeter.AddMember("Id",id+i,allocator);
			//2.���������
			//��������͸��϶�������
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
		PrettyWriter<StringBuffer> pretty_writer(buffer);  //PrettyWriter�Ǹ�ʽ����json�������Writer���ǻ��пո�ѹ�����json
		doc.Accept(pretty_writer);
				
		//��ӡ����Ļ
		cout<<"the PackRecordJsonData output:"<<endl;
		cout<<buffer.GetString()<<endl;

		return buffer.GetString();
	}
	