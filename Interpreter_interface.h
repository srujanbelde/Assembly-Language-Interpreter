class interpreter_inteface
{
public:
	interpreter_inteface() {};
	virtual void lda_command(int address) = 0;
	virtual void ldb_command(int address) = 0;
	virtual void ldi_command(int value) = 0;
	virtual void st_command(int address) = 0;
	virtual void xch_command() = 0;
	virtual void jmp_command(int number) = 0;
	virtual void jzs_command(int number) = 0;
	virtual void jvs_command(int number) = 0;
	virtual void add_command() = 0;
	virtual void hlt_command() = 0;
};