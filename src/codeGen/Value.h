// Value represents an assembly language value; it could be a register or an immediate
union Value {
	int64_t reg_num;
	const std::string *immediate;
};
