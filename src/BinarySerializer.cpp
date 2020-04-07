#include "Hq/BinarySerializer.h"

namespace hq {


void BinarySerializer::operator() (std::string& value, const std::string& s)
{
	size_t len = value.length();
	m_out.write(reinterpret_cast<const char*>(&len), sizeof(len));
	if (len)
		m_out.write(value.c_str(), len);
}


void BinarySerializer::operator() (const std::string& value, const std::string& s)
{
	size_t len = value.length();
	m_out.write(reinterpret_cast<const char*>(&len), sizeof(len));
	if (len)
		m_out.write(value.c_str(), len);
}

void BinarySerializer::operator() (int& value, const std::string& s)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (const int& value, const std::string& s)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (u8& value, const std::string& s)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (const u8& value, const std::string& s)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (u32& value, const std::string& s)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (const u32& value, const std::string& s)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (u64& value, const std::string& s)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (const u64& value, const std::string& s)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (float& value, const std::string& s)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (const float& value, const std::string& s)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (double& value, const std::string& s)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (const double& value, const std::string& s)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}


void BinarySerializer::operator() (entt::entity& value, const std::string& s)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (const entt::entity& value, const std::string& s)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}


void BinarySerializer::operator() (std::string& value)
{
	size_t len = value.length();
	m_out.write(reinterpret_cast<const char*>(&len), sizeof(len));
	if (len)
		m_out.write(value.c_str(), len);
}


void BinarySerializer::operator() (const std::string& value)
{
	size_t len = value.length();
	m_out.write(reinterpret_cast<const char*>(&len), sizeof(len));
	if (len)
		m_out.write(value.c_str(), len);
}

void BinarySerializer::operator() (int& value)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (const int& value)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (u8& value)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (const u8& value)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (u32& value)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (const u32& value)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (u64& value)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (const u64& value)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (float& value)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (const float& value)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (double& value)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (const double& value)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}


void BinarySerializer::operator() (entt::entity& value)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinarySerializer::operator() (const entt::entity& value)
{
	m_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

///////////////// BinaryDeserializer //////////////////


void BinaryDeserializer::operator() (std::string& value, const std::string& s)
{
	size_t len = 0;
	m_in.read(reinterpret_cast<char*>(&len), sizeof(len));
	if (len)
	{
		std::vector<char> tmp(len);
		m_in.read(tmp.data(), len); // deserialize characters of string
		value.assign(tmp.data(), len);
	}
}

void BinaryDeserializer::operator() (u8& value, const std::string& s)
{
	value = 0;
	m_in.read(reinterpret_cast<char*>(&value), sizeof(value));
}

void BinaryDeserializer::operator() (u32& value, const std::string& s)
{
	value = 0;
	m_in.read(reinterpret_cast<char*>(&value), sizeof(value));
}

void BinaryDeserializer::operator() (u64& value, const std::string& s)
{
	value = 0;
	m_in.read(reinterpret_cast<char*>(&value), sizeof(value));
}

void BinaryDeserializer::operator() (float& value, const std::string& s)
{
	value = 0.f;
	m_in.read(reinterpret_cast<char*>(&value), sizeof(value));
}

void BinaryDeserializer::operator() (double& value, const std::string& s)
{
	value = 0.0;
	m_in.read(reinterpret_cast<char*>(&value), sizeof(value));
}



} // hq namespace
