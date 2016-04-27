#include "Base.h"
#include "Container.h"
#include "FabrikaShape.h"
#include "Shapes.h"

void RunAplication(){
	Container< Shape * > containerShapes;
	Fabrika shapeCreator;
	size_t numbe�upportPoints = 0;
	size_t numberShape = 20 + ( rand() % 6 );
	for ( size_t i = 0; i < numberShape; ++i ){
		size_t k = 1 + rand() % 6;
		switch ( k )
		{
		case 1:
			containerShapes.PushFront( shapeCreator.CreaterPoint() );
			break;
		case 2:
			containerShapes.PushFront( shapeCreator.CreatervCircle( numbe�upportPoints ) );
			break;
		case 3:
			containerShapes.PushFront( shapeCreator.CreaterRect( numbe�upportPoints ) );
			break;
		case 4:
			containerShapes.PushFront( shapeCreator.CreaterSquare( numbe�upportPoints ) );
			break;
		case 5:
			containerShapes.PushFront( shapeCreator.CreaterPolyline( numbe�upportPoints ) );
			break;
		case 6:
			containerShapes.PushFront( shapeCreator.CreaterPolygon( numbe�upportPoints ) );
			break;
		default:
			break;
		}
	}
	for ( size_t i = 0; i < numberShape; ++i ){
		try{
			Shape const * shape = *containerShapes.GetElement( i );
			shape->Print();
		}
		catch ( std::invalid_argument & iExcept )
		{
			std::cerr << iExcept.what() << std::endl;
		}
	}
	std::cout << Shape::GetCount() - numbe�upportPoints << '\n';
	while ( containerShapes.GetSize() > 0 ){
		Shape const * shape = *containerShapes.GetHead();
		delete shape;
		containerShapes.RemoveFront();
	}
	std::cout << Shape::GetCount() << '\n';
}

int main(){
	RunAplication();
}