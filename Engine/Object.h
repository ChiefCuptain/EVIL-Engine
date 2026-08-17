#pragma once
#include <string>
#include "JSON.h"
namespace nu
{
	class Object
	{
	public:
		Object() = default;
		Object(std::string name) : m_name{name} {}
		virtual ~Object() = default;

		const std::string& GetName() const { return m_name; }
		bool IsActive() const { return m_active; }
		void SetActive(bool active = true) { m_active = active; }

		virtual void Read(const json::value_t& value)
		{
			JSON_READ_NAME(value, "name", m_name);
			JSON_READ_NAME(value, "active", m_active);
		}

	protected:
		std::string m_name = "<undefined>";
		bool m_active = true;
	};
}