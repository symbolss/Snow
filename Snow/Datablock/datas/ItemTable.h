DATABLOCK_BEGIN(TableItem, "./data/config/item.txt")
	DATABLOCK_PARAM(sint32, id)					//道具ID
	DATABLOCK_PARAM(sint32, itemSpecies)		//物品种类
	DATABLOCK_PARAM(sint32, equipId)			//装备id,类型为装备时有效
	DATABLOCK_PARAM(sint32, bind)				//使用后绑定类型(与ItemBindType对应)
	DATABLOCK_PARAM(sint32, battleUse)			//战斗中是否能使用(与BattleUse对应)
	DATABLOCK_PARAM_STRING(STRING,gemPosition,128)//宝石镶嵌部位
	DATABLOCK_PARAM(sint32, quality)			//品质
	DATABLOCK_PARAM(sint32, needLevel)			//需要级别
	DATABLOCK_PARAM(sint32, prof)				//职业限制,0=不限制职业
	DATABLOCK_PARAM(sint32, repeats)			//最大叠加
	DATABLOCK_PARAM(sint32, maxHave)			//最大拥用(为-1时,没有限制)
	DATABLOCK_PARAM(sint32, broadcast)			//特殊道具公告
	DATABLOCK_PARAM(sint32, batch)				//可否批量使用
	DATABLOCK_PARAM(sint32, dailyLimit)			//每日使用限次
	DATABLOCK_PARAM(sint32, lifeLimit)			//一生总限次
	DATABLOCK_PARAM(sint32, packageId)			//礼包id
	DATABLOCK_PARAM(sint32, qualityType1)		//属性1
	DATABLOCK_PARAM(sint32, qualityNum1)		//属性值1
	DATABLOCK_PARAM(sint32, qualityType2)		//属性2
	DATABLOCK_PARAM(sint32, qualityNum2)		//属性值2
	DATABLOCK_PARAM(sint32, buffid)				//buff组id
	DATABLOCK_PARAM(sint32, cd)					//CD时间
	DATABLOCK_PARAM(sint32, groupcd)			//CD组
	DATABLOCK_PARAM(sint32, destroy)			//是否丢弃
	DATABLOCK_PARAM(sint32, sell)				//是否出售
	DATABLOCK_PARAM(sint32, price)				//售价
	DATABLOCK_PARAM(sint64, test)				//售价
DATABLOCK_END(TableItem,DataBlockHelper::DefaultCallBack)