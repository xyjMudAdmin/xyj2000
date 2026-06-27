// cracked by vikee 2/09/2002   vikee@263.net

string to_chinese(string str)
{
	return CHINESE_D->chinese(str);
}

string chinese_number(int i)
{
	return CHINESE_D->chinese_number(i);
}

int is_chinese(string str)
{
	if (!str)
		return 0;

	return pcre_match(str, "^\\p{Han}+$");
}
