DATABLOCK_BEGIN(TableItem, "./data/config/item.txt")
	DATABLOCK_PARAM(sint32, id)					//����ID
	DATABLOCK_PARAM(sint32, itemSpecies)		//��Ʒ����
	DATABLOCK_PARAM(sint32, equipId)			//װ��id,����Ϊװ��ʱ��Ч
	DATABLOCK_PARAM(sint32, bind)				//ʹ�ú������(��ItemBindType��Ӧ)
	DATABLOCK_PARAM(sint32, battleUse)			//ս�����Ƿ���ʹ��(��BattleUse��Ӧ)
	DATABLOCK_PARAM_STRING(STRING,gemPosition,128)//��ʯ��Ƕ��λ
	DATABLOCK_PARAM(sint32, quality)			//Ʒ��
	DATABLOCK_PARAM(sint32, needLevel)			//��Ҫ����
	DATABLOCK_PARAM(sint32, prof)				//ְҵ����,0=������ְҵ
	DATABLOCK_PARAM(sint32, repeats)			//������
	DATABLOCK_PARAM(sint32, maxHave)			//���ӵ��(Ϊ-1ʱ,û������)
	DATABLOCK_PARAM(sint32, broadcast)			//������߹���
	DATABLOCK_PARAM(sint32, batch)				//�ɷ�����ʹ��
	DATABLOCK_PARAM(sint32, dailyLimit)			//ÿ��ʹ���޴�
	DATABLOCK_PARAM(sint32, lifeLimit)			//һ�����޴�
	DATABLOCK_PARAM(sint32, packageId)			//���id
	DATABLOCK_PARAM(sint32, qualityType1)		//����1
	DATABLOCK_PARAM(sint32, qualityNum1)		//����ֵ1
	DATABLOCK_PARAM(sint32, qualityType2)		//����2
	DATABLOCK_PARAM(sint32, qualityNum2)		//����ֵ2
	DATABLOCK_PARAM(sint32, buffid)				//buff��id
	DATABLOCK_PARAM(sint32, cd)					//CDʱ��
	DATABLOCK_PARAM(sint32, groupcd)			//CD��
	DATABLOCK_PARAM(sint32, destroy)			//�Ƿ���
	DATABLOCK_PARAM(sint32, sell)				//�Ƿ����
	DATABLOCK_PARAM(sint32, price)				//�ۼ�
	DATABLOCK_PARAM(sint64, test)				//�ۼ�
DATABLOCK_END(TableItem,DataBlockHelper::DefaultCallBack)