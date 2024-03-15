#pragma once
#include "../../Lib/Math/Math.h"
#include <array>

class Simplex
{
private:
	std::array<SMath::Vector3, 4> m_points;
	unsigned m_size;

public:
	Simplex() : 
		m_points(
			{ 
				SMath::Vector3::Zero, 
				SMath::Vector3::Zero, 
				SMath::Vector3::Zero, 
				SMath::Vector3::Zero 
			})
		, m_size(0) 
	{}

	Simplex& operator=(std::initializer_list<SMath::Vector3> list)
	{
		for (auto v = list.begin(); v != list.end(); v++)
		{
			m_points[std::distance(list.begin(), v)] = *v;
		}
		m_size = list.size();
		return *this;
	}

	void push_front(SMath::Vector3 point)
	{
		m_points = { point, m_points[0], m_points[1], m_points[2] };
		m_size = std::min(m_size + 1, 4u);
	}

	SMath::Vector3& operator[](unsigned i) { return m_points[i]; }
	unsigned size() const { return m_size; }

	auto begin() const { return m_points.begin(); }
	auto end() const { return m_points.end() - (4 - m_size); }
};

