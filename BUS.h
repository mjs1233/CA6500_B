#pragma once
template <typename data_type>
class BUS
{
private:
	data_type data;

public:
	void setData(data_type data)
	{
		this->data = data;
	}

	data_type getData()
	{
		return this->data;
	}

};