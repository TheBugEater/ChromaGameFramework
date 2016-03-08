#ifndef CGFTYPES_H
#define CGFTYPES_H

#if defined(_CGFEngineDLL)
#define CGF_DLL     __declspec(dllexport)
#else         /* use a DLL library */
#define CGF_DLL     __declspec(dllimport)
#endif

#include <windows.h>
#include <tchar.h>
#include <math.h>
#include "Box2d/Box2D.h"

#pragma warning( disable: 4251 )

#define M_PI       3.14159265358979323846

namespace CGF
{

	static const double Deg2Rad = M_PI / 180;
	static const double Rad2Deg = 180 / M_PI;

	struct CGF_DLL CGFSize
	{
		CGFSize(int width, int height) : Width(width), Height(height) {}
		CGFSize() : Width(1), Height(1) {}

		int Width;
		int Height;
	};

	struct CGF_DLL CGFVector
	{
		CGFVector(int x, int y) : X((float)x), Y((float)y) {}
		CGFVector(float x, float y) : X(x), Y(y) {}
		CGFVector() : X(0), Y(0) {}
		CGFVector(b2Vec2 vec) : X(vec.x), Y(vec.y) {}

		// static CGFVector ZeroVector(0, 0);
		CGFVector& operator+= (CGFVector Vector)
		{
			this->X += Vector.X;
			this->Y += Vector.Y;

			return *this;
		}

		CGFVector& operator-= (CGFVector Vector)
		{
			this->X -= Vector.X;
			this->Y -= Vector.Y;

			return *this;
		}

		CGFVector& operator*= (float Value)
		{
			this->X *= Value;
			this->Y *= Value;

			return *this;
		}

		CGFVector& operator/= (float Value)
		{
			this->X /= Value;
			this->Y /= Value;

			return *this;
		}

		CGFVector operator+ (CGFVector Vector)
		{
			return CGFVector(this->X + Vector.X, this->Y + Vector.Y);
		}

		CGFVector operator- (CGFVector Vector)
		{
			return CGFVector(this->X - Vector.X, this->Y - Vector.Y);
		}

		bool operator == (CGFVector Vector)
		{
			if (this->X == Vector.X && this->Y == Vector.Y)
			{
				return true;
			}

			return false;
		}

		float Distance(CGFVector Vector)
		{
			return sqrt(pow((this->X - Vector.X), 2) + pow((this->Y - Vector.Y), 2));
		}

		float Length()
		{
			return sqrt((this->X * this->X) + (this->Y * this->Y));
		}
		
		CGFVector Normalize()
		{
			CGFVector Vector;
			float Length = this->Length();

			Vector.X = this->X / Length;
			Vector.Y = this->Y / Length;

			return Vector;
		}

		float Dot(CGFVector Vector)
		{
			return ((this->X * Vector.X) + (this->Y * Vector.Y));
		}

		float Angle(CGFVector Vector)
		{
			return acos(Dot(Vector) / this->Length() * Vector.Length());
		}

		b2Vec2 ToB2Vec()
		{
			return b2Vec2(X, Y);
		}

		float X;
		float Y;
	};

	enum class CGF_DLL CGFColors : COLORREF
	{
		Maroon = RGB(128, 0, 0),
		DarkRed = RGB(139, 0, 0),
		Brown = RGB(165, 42, 42),
		FireBrick = RGB(178, 34, 34),
		Crimson = RGB(220, 20, 60),
		Red = RGB(255, 0, 0),
		Tomato = RGB(255, 99, 71),
		Coral = RGB(255, 127, 80),
		IndianRed = RGB(205, 92, 92),
		LightCoral = RGB(240, 128, 128),
		DarkSalmon = RGB(233, 150, 122),
		Salmon = RGB(250, 128, 114),
		LightSalmon = RGB(255, 160, 122),
		OrangeRed = RGB(255, 69, 0),
		DarkOrange = RGB(255, 140, 0),
		Orange = RGB(255, 165, 0),
		Gold = RGB(255, 215, 0),
		DarkGoldenRod = RGB(184, 134, 11),
		GoldenRod = RGB(218, 165, 32),
		PaleGoldenRod = RGB(238, 232, 170),
		DarkKhaki = RGB(189, 183, 107),
		Khaki = RGB(240, 230, 140),
		Olive = RGB(128, 128, 0),
		Yellow = RGB(255, 255, 0),
		YellowGreen = RGB(154, 205, 50),
		DarkOliveGreen = RGB(85, 107, 47),
		OliveDrab = RGB(107, 142, 35),
		LawnGreen = RGB(124, 252, 0),
		ChartReuse = RGB(127, 255, 0),
		GreenYellow = RGB(173, 255, 47),
		DarkGreen = RGB(0, 100, 0),
		Green = RGB(0, 128, 0),
		ForestGreen = RGB(34, 139, 34),
		Lime = RGB(0, 255, 0),
		LimeGreen = RGB(50, 205, 50),
		LightGreen = RGB(144, 238, 144),
		PaleGreen = RGB(152, 251, 152),
		DarkSeaGreen = RGB(143, 188, 143),
		MediumSpringGreen = RGB(0, 250, 154),
		SpringGreen = RGB(0, 255, 127),
		SeaGreen = RGB(46, 139, 87),
		MediumAquaMarine = RGB(102, 205, 170),
		MediumSeaGreen = RGB(60, 179, 113),
		LightSeaGreen = RGB(32, 178, 170),
		DarkSlateGray = RGB(47, 79, 79),
		Teal = RGB(0, 128, 128),
		DarkCyan = RGB(0, 139, 139),
		Aqua = RGB(0, 255, 255),
		Cyan = RGB(0, 255, 255),
		LightCyan = RGB(224, 255, 255),
		DarkTurquoise = RGB(0, 206, 209),
		Turquoise = RGB(64, 224, 208),
		MediumTurquoise = RGB(72, 209, 204),
		PaleTurquoise = RGB(175, 238, 238),
		AquaMarine = RGB(127, 255, 212),
		PowderBlue = RGB(176, 224, 230),
		CadetBlue = RGB(95, 158, 160),
		SteelBlue = RGB(70, 130, 180),
		CornFlowerBlue = RGB(100, 149, 237),
		DeepSkyBlue = RGB(0, 191, 255),
		DodgerBlue = RGB(30, 144, 255),
		LightBlue = RGB(173, 216, 230),
		SkyBlue = RGB(135, 206, 235),
		LightSkyBlue = RGB(135, 206, 250),
		MidnightBlue = RGB(25, 25, 112),
		Navy = RGB(0, 0, 128),
		DarkBlue = RGB(0, 0, 139),
		MediumBlue = RGB(0, 0, 205),
		Blue = RGB(0, 0, 255),
		RoyalBlue = RGB(65, 105, 225),
		BlueViolet = RGB(138, 43, 226),
		Indigo = RGB(75, 0, 130),
		DarkSlateBlue = RGB(72, 61, 139),
		SlateBlue = RGB(106, 90, 205),
		MediumSlateBlue = RGB(123, 104, 238),
		MediumPurple = RGB(147, 112, 219),
		DarkMagenta = RGB(139, 0, 139),
		DarkViolet = RGB(148, 0, 211),
		DarkOrchid = RGB(153, 50, 204),
		MediumOrchid = RGB(186, 85, 211),
		Purple = RGB(128, 0, 128),
		Thistle = RGB(216, 191, 216),
		Plum = RGB(221, 160, 221),
		Violet = RGB(238, 130, 238),
		Magenta = RGB(255, 0, 255),
		Orchid = RGB(218, 112, 214),
		MediumVioletRed = RGB(199, 21, 133),
		PaleVioletRed = RGB(219, 112, 147),
		DeepPink = RGB(255, 20, 147),
		HotPink = RGB(255, 105, 180),
		LightPink = RGB(255, 182, 193),
		Pink = RGB(255, 192, 203),
		AntiqueWhite = RGB(250, 235, 215),
		Beige = RGB(245, 245, 220),
		Bisque = RGB(255, 228, 196),
		BlanchedAlmond = RGB(255, 235, 205),
		Wheat = RGB(245, 222, 179),
		CornSilk = RGB(255, 248, 220),
		LemonChiffon = RGB(255, 250, 205),
		LightGoldenRodYellow = RGB(250, 250, 210),
		LightYellow = RGB(255, 255, 224),
		SaddleBrown = RGB(139, 69, 19),
		Sienna = RGB(160, 82, 45),
		Chocolate = RGB(210, 105, 30),
		Peru = RGB(205, 133, 63),
		SandyBrown = RGB(244, 164, 96),
		BurlyWood = RGB(222, 184, 135),
		Tan = RGB(210, 180, 140),
		RosyBrown = RGB(188, 143, 143),
		Moccasin = RGB(255, 228, 181),
		NavajoWhite = RGB(255, 222, 173),
		PeachPuff = RGB(255, 218, 185),
		MistyRose = RGB(255, 228, 225),
		LavenderBlush = RGB(255, 240, 245),
		Linen = RGB(250, 240, 230),
		OldLace = RGB(253, 245, 230),
		PapayaWhip = RGB(255, 239, 213),
		SeaShell = RGB(255, 245, 238),
		MintCream = RGB(245, 255, 250),
		SlateGray = RGB(112, 128, 144),
		LightSlateGray = RGB(119, 136, 153),
		LightSteelBlue = RGB(176, 196, 222),
		Lavender = RGB(230, 230, 250),
		FloralWhite = RGB(255, 250, 240),
		AliceBlue = RGB(240, 248, 255),
		GhostWhite = RGB(248, 248, 255),
		Honeydew = RGB(240, 255, 240),
		Ivory = RGB(255, 255, 240),
		Azure = RGB(240, 255, 255),
		Snow = RGB(255, 250, 250),
		Black = RGB(0, 0, 0),
		DimGray = RGB(105, 105, 105),
		Gray = RGB(128, 128, 128),
		DarkGray = RGB(169, 169, 169),
		Silver = RGB(192, 192, 192),
		LightGray = RGB(211, 211, 211),
		Gainsboro = RGB(220, 220, 220),
		WhiteSmoke = RGB(245, 245, 245),
		White = RGB(255, 255, 255)
	};

	enum class CGFKeys
	{
		KEY_ESC,
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		KEY_PRNTSCR,
		KEY_SCRLCK,
		KEY_BREAK,

		KEY_M1,
		KEY_TIDE,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_0,
		KEY_HYPHEN,
		KEY_EQUAL,
		KEY_BACKSPACE,
		KEY_INS,
		KEY_HOME,
		KEY_PAGEUP,
		KEY_NUMLCK,
		KEY_DIVIDE,
		KEY_MULTIPLY,
		KEY_MINUS,
		
		KEY_M2,
		KEY_TAB,
		KEY_Q,
		KEY_W,
		KEY_E,
		KEY_R,
		KEY_T,
		KEY_Y,
		KEY_U,
		KEY_I,
		KEY_O,
		KEY_P,
		KEY_OPENBRACE,
		KEY_CLOSEBRACE,
		KEY_,
		KEY_DEL,
		KEY_END,
		KEY_PAGEDOWN,
		KEY_NUM7,
		KEY_NUM8,
		KEY_NUM9,
		KEY_PLUS,

		KEY_M3,
		KEY_CAPS,
		KEY_A,
		KEY_S,
		KEY_D,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_SEMICOLON,
		KEY_APOSTROPHE,
		KEY_ENTER,
		KEY_NUM4,
		KEY_NUM5,
		KEY_NUM6,

		KEY_M4,
		KEY_LSHIFT,
		KEY_Z,
		KEY_X,
		KEY_C,
		KEY_V,
		KEY_B,
		KEY_N,
		KEY_M,
		KEY_COMMA,
		KEY_DOT,
		KEY_QUESTIONMARK,
		KEY_RSHIFT,
		KEY_UP,
		KEY_NUM1,
		KEY_NUM2,
		KEY_NUM3,
		
		KEY_M5,
		KEY_LCTRL,
		KEY_WINKEY,
		KEY_LALT,
		KEY_SPACE,
		KEY_RALT,
		KEY_FN,
		KEY_OPTION,
		KEY_RCTRL,
		KEY_LEFT,
		KEY_DOWN,
		KEY_RIGHT,
		KEY_NUM0,
		KEY_NUMDEL,
		KEY_NUMENTER
	};

	template <typename T>
	T Clamp(const T& n, const T& lower, const T& upper)
	{
		return max(lower, min(n, upper));
	}

	static float Blend(float a, float b, float alpha)
	{
		return (1.f - alpha) * a + alpha * b;
	}

	static COLORREF ColorBlend(const COLORREF& a, const COLORREF& b, float alpha)
	{
		COLORREF x = RGB(Blend(GetRValue(a), GetRValue(b), alpha),
			Blend(GetGValue(a), GetGValue(b), alpha),
			Blend(GetBValue(a), GetBValue(b), alpha));

		return x;
	}

	static CGFVector& Rotate(CGFVector& position, CGFVector& origin, float degrees)
	{
		double sinValue = sin(degrees * Deg2Rad);
		double cosValue = cos(degrees * Deg2Rad);

		float tx = position.X - origin.X;
		float ty = position.Y - origin.Y;

		position.X = (float)(cosValue * tx) - (float)(sinValue * ty) + origin.X;
		position.Y = (float)(sinValue * tx) + (float)(cosValue * ty) + origin.Y;

		return position;
	}
}
#endif //CGFTYPES_H