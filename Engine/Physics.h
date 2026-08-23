#include <box2d/box2d.h>
#include <memory>

namespace nu
{
	class Physics
	{
	public:
		Physics() = default;

		bool Initialize();
		void Quit();

		void Update(float dt);

	private:
		b2WorldId m_worldId;
	};
}
