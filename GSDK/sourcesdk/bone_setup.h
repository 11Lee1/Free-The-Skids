int Studio_BoneIndexByName(CStudioHdr* pStudioHdr, char const* pName)
{
	int start = 0, end = pStudioHdr->numbones() - 1;
	const byte* pBoneTable = pStudioHdr->GetBoneTableSortedByName();
	mstudiobone_t *pbones = pStudioHdr->pBone(0);

	while (start <= end)
	{
		int mid = (start + end) >> 1;
		int cmp = Q_stricmp(pbones[pBoneTable[mid]].pszName(), pName);

		if (cmp < 0)
		{
			start = mid + 1;
		}
		else if (cmp > 0)
		{
			end = mid - 1;
		}
		else
		{
			return pBoneTable[mid];
		}
	}
	return -1;
}