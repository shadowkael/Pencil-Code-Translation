int htoi(char *s,int size){
	int n=0;
	for (int i=0;i<size;i++){
		if (s[i]=='0'&&s[i+1]!='x')
			continue;
		else if(s[i]>='0'&&s[i]<='9')
			n=16*n+(s[i]-'0');
		else if(s[i]>='a'&&s[i]<='f')
			n=n*16+(s[i]-87);
		else if(s[i]>='A'&&s[i]<='F')
			n=n*16+(s[i]-55);
	}
	return n;
}
