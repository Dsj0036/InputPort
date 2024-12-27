#pragma once
#include "System.h"
#include "math.h"
#include "cmath"
typedef struct Vector2
{
	static Vector2 Empty;
	float x, y;
	Vector2()
	{
		this->x = this->y = 0;
	}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	bool operator==(Vector2& Vec)
	{
		return (this->x == Vec.x && this->y == Vec.y);
	}
	const Vector2 operator- (Vector2 const& Vector)
	{
		return { this->x - Vector.x, this->y - Vector.y };
	}
	const Vector2 operator+ (Vector2 const& Vector)
	{
		return { this->x + Vector.x, this->y + Vector.y };
	}
	const Vector2 operator/ (Vector2 const& Vector)
	{
		return { this->x / Vector.x, this->y / Vector.y };
	}
	const Vector2 operator/ (float xy)
	{
		return { this->x / xy, this->y / xy };
	}
	const Vector2 operator* (Vector2 const& Vector)
	{
		return { this->x * Vector.x, this->y * Vector.y };
	}
	Vector2 Clamp(const Vector2& minBounds, const Vector2& maxBounds) const {
		float x = fminf(fmaxf(this->x, minBounds.x), maxBounds.x);
		float y = fminf(fmaxf(this->y, minBounds.y), maxBounds.y);
		return { x, y };
	}
	Vector2 Clamp(const Vector2& bounds) {
		float x = fminf(this->x, bounds.x);
		float y = fminf(this->y, bounds.y);
		return { x, y };
	}
	void Clamp2(Vector2 min, Vector2 max) {
		this->x = fminf(fmaxf(this->x, min.x), max.x);
		this->y = fminf(fmaxf(this->y, min.y), max.y);
	}
	void Clamp2(float minimumX, float minimumY, float maximumX, float maximumY) {
		this->x = fminf(fmaxf(this->x, minimumX), maximumX);
		this->y = fminf(fmaxf(this->y, minimumY), maximumY);
	}

}Vector2, * PVector2, vec2, Vec2;

Vector2 Vector2::Empty{ 0,0 };

typedef struct Vector3
{
	static Vector3 Empty;

	float x, y, z;
	Vector3()
	{
		x = y = z = 0;
	}
	Vector3(float x, float y, float z)
	{
		this->x = x; this->y = y; this->z = z;
	}
	Vector3 operator-(void) const {
		return { -x, -y, -z };
	}
	const bool operator==(const Vector3& v) const {
		return x == v.x && y == v.y && z == v.z;
	}
	const bool operator!=(const Vector3& v) const {
		return !(*this == v);
	}
	const Vector3 operator+(const Vector3& v) const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	const Vector3& operator-(const Vector3& v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	const Vector3& operator*(float fl) const {
		return Vector3(x * fl, y * fl, z * fl);
	}
	const Vector3& operator/(float fl) const {
		return Vector3(x / fl, y / fl, z / fl);
	}
	const float Length(void) const {
		return (float)sqrtf(x * x + y * y + z * z);
	}
	float getLength() const {
		return sqrtf((x * x) + (y * y) + (z * z));
	}
	const Vector3 Normalize(void) const
	{
		float flLen = Length();
		if (flLen == 0) return Vector3(0, 0, 1);
		flLen = 1 / flLen;
		return Vector3(x * flLen, y * flLen, z * flLen);
	}

	float Distance(Vector3 const& Vector)
	{
		return sqrtf(DistanceEx(Vector));
	}
	float DistanceEx(Vector3 const& Vector)
	{
		float _x = this->x - Vector.x, _y = this->y - Vector.y, _z = this->z - Vector.z;
		return ((_x * _x) + (_y * _y) + (_z * _z));
	}
	float DotProduct(Vector3 const& Vector)
	{
		return (this->x * Vector.x) + (this->y * Vector.y) + (this->z * Vector.z);
	}
	const Vector3& RoundHalfUp()
	{
		return Vector3(floor(this->x + 0.5), floor(this->y + 0.5), floor(this->z + 0.5));
	}
	const Vector3& RoundHalfDown()
	{
		return Vector3(floor(this->x + 0.5), floor(this->y + 0.5), floor(this->z + 0.5));
	}
	Vector3 cross(const Vector3& other) const {
		return Vector3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	float dot(const Vector3& other) const {
		return x * other.x + y * other.y + z * other.z;
	}



} Vector3, * PVector3, vec3, Vec3;
Vector3 Vector3::Empty{ 0,0,0 };

typedef struct Rectangle {
public:
	Rectangle(Vector2 pos, Vector2 size) :Position(pos), Size(size) {

	}
	Rectangle(float x, float y, float sX, float sY) :Position(x, y), Size(sX, sY) {

	}
	Rectangle() {

	}
	Vector2 Position;
	Vector2 Size;

	Rectangle NextCenter() {
		return Rectangle({ Position.x + (Size.x / 2), Position.y }, Size);
	}
	Rectangle Scale(float rate) {

		return Rectangle({ Position.x, Position.y }, { Size.x * rate, Size.y * rate });
	}
	Rectangle operator/(float last_center) {
		return Rectangle({ Position.x - (Size.x / last_center), Position.y }, Size);
	}
	Rectangle operator*(float rescale) {
		return Scale(rescale);
	}
	Rectangle incX(float x) {
		return Rectangle({ Position.x + x, Position.y }, Size);
	}
	Rectangle incY(float y) {
		return Rectangle({ Position.x, Position.y + y }, Size);
	}
	Rectangle incWidth(float x) {
		return Rectangle({ Position.x, Position.y }, { Size.x + x, Size.y });
	}
	Rectangle incHeight(float y) {
		return Rectangle({ Position.x, Position.y }, { Size.x , Size.y + y });
	}
	bool Contains(const Vector2& point) const {
		return (point.x >= Position.x && point.x <= Position.x + Size.x &&
			point.y >= Position.y && point.y <= Position.y + Size.y);
	}
	static Rectangle fromAbsolute(float x, float y, float sX, float sY) {
		return { {x,y}, {sX - x, sY - y} };
	}

	static Rectangle rect(float x, float y, float width, float height) {
		return { {x,y}, { width, height } };
	}

	const Rectangle& operator/(double stub) {
		return rect(this->Position.x / 2.0f, this->Position.y / 2.0f, this->Size.x / 2.0f, this->Size.y / 2.0f);
	}
	bool operator != (const Rectangle& x) {
		return x.Size.x != Size.x || x.Size.y != Size.y || Position.x != x.Position.x || Position.y != x.Position.y;
	}
	bool operator ==(const Rectangle& x) {
		return !this->operator!=(x);
	}
	const static Rectangle Empty;
};
const Rectangle Rectangle::Empty{ {0,0}, { 0,0 } };
Rectangle glRect(float x, float y, float width, float height) {
	return { {x,y}, { width, height } };
}

class VertexData
{
public:

	VertexData() {
		startX = 0;
		startY = 0;
		endX = 0;
		endY = 0;
		Sprite = glRect(0, 0, 0, 0);
	}
	static const VertexData Empty;
	VertexData(Vector2 size) :Size(size) {

	}
	VertexData(Rectangle bounds, Vector2 atlasDimensions) {
		Size = atlasDimensions;
		Sprite = bounds;
		Set(bounds);
	}

	VertexData(Rectangle bounds, int atlasDimension) {
		Size = Vector2(atlasDimension, atlasDimension);
		Sprite = bounds;
		Set(bounds);
	}
	// u1
	float startX;
	// v1
	float startY;
	// u2
	float endX;
	// v2
	float endY;
	// Atlas Size 
	Vector2 Size;
	Rectangle Sprite;
	void Set(Rectangle rect) {
		float x2, y2;
		x2 = rect.Position.x + rect.Size.x;
		y2 = rect.Position.y + rect.Size.y;


		float u1 = rect.Position.x / Size.x;
		float v1 = rect.Position.y / Size.y;
		float u2 = x2 / Size.x;
		float v2 = y2 / Size.y;

		startX = u1;
		startY = v1;
		endX = u2;
		endY = v2;
		Sprite = rect;
	}
	float operator[](byte index) {
		switch (index) {
		case 0: return startX;
		case 1: return startY;
		case 2: return endX;
		case 3: return endY;
		default:return -1;
		}
	}

	float u1()const {
		return startX;
	}
	float v1()const {
		return startY;
	}
	float u2()const {
		return endX;
	}
	float v2()const {
		return endY;
	}
	bool isEmpty() const {
		return startX == 0 &&
			startY == 0 &&
			endX == 0 &&
			endY == 0;
	}
	static VertexData New(Vector2 origin, Vector2 size, Vector2 baseDimensions) {
		return { { origin, size }, baseDimensions };
	};

};

const VertexData VertexData::Empty{};