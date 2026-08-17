#pragma once
#include "pch.h"
#include "Object.h"
#include "Singleton.h"
#include "StringUtils.h"
#include <iostream>
#include <memory>
#include <map>
#include <string>

#define FACTORY_REGISTER(classname)										\
    class Register##classname											\
    {																	\
	public:																\
		Register##classname()											\
		{																\
			nu::Factory::Instance().Register<classname>(#classname);	\
		}																\
	};																	\
	static Register##classname register##classname;

namespace nu
{
	class ICreator
	{
	public:
		virtual ~ICreator() = default;
		virtual std::unique_ptr<Object> Create() = 0;
	};

	template <typename T>
		requires std::derived_from<T, Object>
	class Creator : public ICreator
	{
		std::unique_ptr<Object> Create() override { return std::make_unique<T>(); }
	};

	class Factory : public Singleton<Factory>
	{
	public:
		template <typename T = class Object>
			requires std::derived_from<T, Object>
		inline void Register(const std::string& name)
		{
			std::string lower = string::ToLower(name);

			if (m_registry.contains(lower))
			{
				std::cerr << "Object already registered : " << name << "\n";
				return;
			}

			std::cout << "Object registered : " << name << "\n";

			m_registry[lower] = std::make_unique<Creator<T>>();
		}

		template <typename T = class Object>
			requires std::derived_from<T, Object>
		inline std::unique_ptr<T> Create(const std::string& name)
		{
			std::string lower = string::ToLower(name);

			if (!m_registry.contains(lower))
			{
				std::cerr << "Object not registered : " << name << "\n";
				return std::unique_ptr<T>();
			}

			auto iter = m_registry.find(lower);

			auto object = iter->second->Create();

			T* derived = dynamic_cast<T*>(object.get());
			if (derived)
			{
				object.release();
				return std::unique_ptr<T>(derived);
			}
			else
			{
				std::cerr << "Object not derived from type : " << name << "\n";
			}
			return std::unique_ptr<T>();

		}

	private:
		std::map<std::string, std::unique_ptr<ICreator>> m_registry;
	};
	

		
}