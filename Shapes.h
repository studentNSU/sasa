#ifndef __Shapes_H_
#define __Shapes_H_

#define _USE_MATH_DEFINES 
#include <math.h>

#include "Base.h"
#include "Container.h"

class Shape : public Printable{
public:
	Shape(){
		GetCount(1);
	}
	static size_t GetCount( int iDelta = 0 ){
		static size_t size = 0;
		return size += iDelta;
	}
	virtual ~Shape(){ //?
		GetCount( -1 );
	}
};

class Point : public Shape{
public:
	Point(){}
	Point(  Point const & iPoint ){ m_x = iPoint.GetX(); m_y = iPoint.GetY(); }
	Point( double iX, double iY ) 
		: m_x( iX )
		, m_y( iY )
	{}
	double GetX() const { return m_x; }
	double GetY() const { return m_y; }
	void Print() const {
		std::cout << "Point"  << '\t' << *this << '\n';
	}
	friend std::ostream & operator << ( std::ostream & iStream,  Point const & iPoint );
	virtual ~Point(){}
private:
	double m_x;
	double m_y;
};

std::ostream & operator << ( std::ostream & iStream,  Point const & iPoint ) {
	return iStream << '(' << iPoint.m_x << ',' << iPoint.m_y << ')';
}

class Circle : public Shape {
public:
	Circle( Point const & iCenter, double iRadius )
		: m_centre( iCenter )
		, m_radius( iRadius )
	{
		m_area = M_PI * pow( m_radius, 2 );
	}
	void Print() const {
		std::cout << "Circle with" << '\t' << *this << '\n';
	}
	virtual ~Circle(){}
	friend std::ostream & operator << ( std::ostream & iStream, Circle const & iCircle );
private:
	Point  m_centre;
	double m_radius;
	double m_area;
};
std::ostream & operator << ( std::ostream & iStream, Circle const & iCircle ) {
	return iStream << "centre = " << iCircle.m_centre<< '\t' << "radius=" << iCircle.m_radius << '\t' << "area=" << iCircle.m_area;
}

class Rect : public Shape {
public:
	Rect( Point const & iFirstvertex, Point const & iSecondvertex )
		: m_firstVertex( iFirstvertex )
		, m_secondVertex( iSecondvertex )
	{
		double length = abs( m_firstVertex.GetX() - m_secondVertex.GetX() );
		double breadth = abs( m_firstVertex.GetY() - m_secondVertex.GetY() );
		m_area = length * breadth;
		m_perimeter = 2 * length + 2 * breadth;
	}
	virtual ~Rect(){}
	void Print() const {
		std::cout << "Rect with"  << '\t' << *this << '\n';
	}
	friend std::ostream & operator << ( std::ostream & iStream, Rect const & iRect );
private:
	Point m_firstVertex;
	Point m_secondVertex;
	double m_area;
	double m_perimeter;
};
std::ostream & operator << ( std::ostream & iStream, Rect const & iRect ) {
	return iStream << "area = " << iRect.m_area << '\t' << "perimeter = " << iRect.m_perimeter;
}

class Square : public Shape {
public:
	Square( Point const & iVertex, double iLengthSide )
		: m_vertex( iVertex )
		, m_lengthSide( iLengthSide )
	{
		m_area = pow( m_lengthSide, 2 );
		m_perimeter = 4 * m_lengthSide;
	}
	virtual ~Square(){}
	void Print() const {
		std::cout << "Square with" << '\t' << *this << '\n';
	}
	friend std::ostream & operator << ( std::ostream & iStream, Square const & iSquare );
private:
	Point m_vertex;
	double m_lengthSide;
	double m_area;
	double m_perimeter;
};
std::ostream & operator << ( std::ostream & iStream, Square const & iSquare ) {
	return iStream << "area = " << iSquare.m_area << '\t' << "perimeter = " << iSquare.m_perimeter;
}

class Polyline : public Shape {
public:
	Polyline() {
		m_lenght = 0;
		m_vertexes = new  Container < Point > ;
	}
	void AddPoint( Point const & iPoint ){
		Point const * tailPoint = m_vertexes->GetTail();
		if ( m_vertexes->GetSize() > 0 ){
			m_lenght += sqrt( pow( iPoint.GetX() - tailPoint->GetX(), 2 ) + pow( iPoint.GetY() - tailPoint->GetY(), 2 ) );
		}
		m_vertexes->PushBack( iPoint );
	}
	virtual ~Polyline(){
		delete m_vertexes;
	}
	void Print() const {
		if ( m_vertexes->GetSize() < 2 ){
			throw std::invalid_argument( "The broken line should contain more than 1 point." );
		}
		std::cout << "Polyline with" << '\t' << *this << '\n';
	}
	friend std::ostream & operator << ( std::ostream & iStream, Polyline const & iPolyline );
private:
	Container< Point > * m_vertexes;
	double m_lenght;
};
std::ostream & operator << ( std::ostream & iStream, Polyline const & iPolyline ) {
	return iStream << "lenght = " << iPolyline.m_lenght;
}

class Polygon : public Shape {
public:
	Polygon() {
		m_vertexes = new  Container < Point >;
		m_perimeter = 0;
	}
	void AddPoint( Point const& iPoint ){
		Point const * tailPoint = m_vertexes->GetTail();
		if ( m_vertexes->GetSize() > 0 ){
			m_perimeter += sqrt( pow( iPoint.GetX() - tailPoint->GetX(), 2 ) + pow( iPoint.GetY() - tailPoint->GetY(), 2 ) );
		}
		m_vertexes->PushBack( iPoint );
	}
	virtual ~Polygon(){
		delete m_vertexes;
	}
	void Print() const {
		if ( m_vertexes->GetSize() < 3 ){
			throw std::invalid_argument( "Polygon has to contain more than 2 points." );
		}
		std::cout << "Polygon with" << '\t' << *this << '\n';
	}
	friend std::ostream & operator << ( std::ostream & iStream, Polygon const & iPolygon );
private:
	Container< Point > * m_vertexes;
	double m_perimeter;
};
std::ostream & operator << ( std::ostream & iStream, Polygon const & iPolygon ) {
	Point const * headVertex = iPolygon.m_vertexes->GetHead();
	Point const * tailVertex = iPolygon.m_vertexes->GetTail();
	return iStream << "perimeter = " << iPolygon.m_perimeter + sqrt( pow( headVertex->GetX() - tailVertex->GetX(), 2 ) + pow( headVertex->GetY() - tailVertex->GetY(), 2 ) );
}
#endif // __Shapes_H_