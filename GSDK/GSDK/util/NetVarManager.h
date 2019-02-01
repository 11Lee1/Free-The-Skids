// another big paste. b1g lazy
class CNetworkedVariableManager {
public:
	CNetworkedVariableManager(void) {
		m_tables.clear();
		ClientClass *clientClass = client()->GetAllClasses();
		if (!clientClass)
		{
			return;
		}
		while (clientClass)
		{
			RecvTable *recvTable = clientClass->m_pRecvTable;
			m_tables.push_back(recvTable);
			clientClass = clientClass->m_pNext;
		}
	}
	int GetOffset(const char *tableName, const char *propName)
	{
		int offset = GetProp(tableName, propName);
		if (!offset)
		{
			return 0;
		}
		return offset;
	}

	DWORD HookProp(const char *tableName, const char *propName, RecvVarProxyFn function)
	{
		RecvProp *recvProp = 0;
		GetProp(tableName, propName, &recvProp);
		if (!recvProp)
		{
			return NULL;
		}
		DWORD oProxy = (DWORD)recvProp->m_ProxyFn;
		recvProp->m_ProxyFn = function;
		return oProxy;
	}
	std::vector<RecvTable*> m_tables;
private:
	int GetProp(const char *tableName, const char *propName, RecvProp **prop = 0)
	{
		RecvTable *recvTable = GetTable(tableName);
		if (!recvTable)
		{
			return 0;
		}
		int offset = GetProp(recvTable, propName, prop);
		if (!offset)
		{
			return 0;
		}
		return offset;
	}
	int GetProp(RecvTable *recvTable, const char *propName, RecvProp **prop = 0)
	{
		int extraOffset = 0;
		for (int i = 0; i < recvTable->m_nProps; ++i)
		{
			RecvProp *recvProp = &recvTable->m_pProps[i];
			RecvTable *child = recvProp->m_pDataTable;
			if (child
				&& (child->m_nProps > 0))
			{
				int tmp = GetProp(child, propName, prop);

				if (tmp)
				{
					extraOffset += (recvProp->m_Offset + tmp);
				}
			}


			if (_stricmp(recvProp->m_pVarName, propName))
			{
				continue;
			}
			if (prop)
			{
				*prop = recvProp;
			}
			return (recvProp->m_Offset + extraOffset);
		}
		return extraOffset;
	}
	RecvTable *GetTable(const char *tableName)
	{
		if (m_tables.empty())
		{
			return 0;
		}
		for (RecvTable *table : m_tables)
		{
			if (!table)
			{
				continue;
			}
			if (_stricmp(table->m_pNetTableName, tableName) == 0)
			{
				return table;
			}
		}
		return 0;
	}



	void DumpTableNames()
	{
		if (m_tables.empty())
			return;

		for (RecvTable *table : m_tables)
		{
			if (!table)
				continue;
			print("%s\n",table->m_pNetTableName);
			
		}
	}
};