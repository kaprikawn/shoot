#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <math.h>

class Vector {
  private:
    float x_;
    float y_;
    
  public:
    Vector( float x, float y ) : x_( x ), y_( y ) {}
    ~Vector(){}
    
    float getX() { return x_; }
    float getY() { return y_; }
    
    void setX( float x ) { x_ = x; }
    void setY( float y ) { y_ = y; }
    
    float length() { return sqrt( x_ * x_ + y_ * y_ ); }
    
    Vector operator+( const Vector& v2 ) const {
      return Vector( x_ + v2.x_, y_ + v2.y_ );
    }
    
    friend Vector& operator+=( Vector& v1, const Vector& v2 ) {
      v1.x_ += v2.x_;
      v1.y_ += v2.y_;
      return v1;
    }
    
    Vector operator*( float scaler ) {
      return Vector( x_ * scaler, y_ * scaler );
    }
    
    Vector& operator*=( float scaler ) {
      x_ *= scaler;
      y_ *= scaler;
      return *this;
    }
    
    Vector operator-( const Vector& v2 ) const {
      return Vector( x_ - v2.x_, y_ - v2.y_ );
    }
    
    friend Vector& operator-=( Vector& v1, const Vector& v2 ) {
      v1.x_ -= v2.x_;
      v1.y_ -= v2.y_;
      return v1;
    }
    
    Vector operator/( float scaler ) {
      return Vector( x_ / scaler, y_ / scaler );
    }
    
    Vector& operator/=( float scaler ) {
      x_ /= scaler;
      y_ /= scaler;
      
      return *this;
    }
    
    void normalize() {
      float l = length();
      if( l > 0 ) {
        ( *this ) *= 1 / l;
      }
    }
  
    float distance( const Vector& v2 ) {
      return sqrt( pow( ( x_ - v2.x_ ), 2 ) +  pow( ( y_ - v2.y_ ), 2 ) );
    }
};

#endif //VECTOR_HPP
