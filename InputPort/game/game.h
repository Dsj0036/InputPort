#pragma once
#include "System.h"
namespace Minecraft {

	

	bool getMustLoopProcess();

	// Gets whether the user is really in game and ready.
	inline bool getGameStarted();
	


	class app {
	public:
		any addLocalPlayer(int a1);
		any GetMiniGame();
		any GetClientMasterGameMode();
		any run();
		any getCameraEntity();
		any createPrimaryLocalPlayer(int a1);
		any setLocalPlayerIdx(int a1);
		any getLocalPlayerIdx();
		any tickAllConnections();
		any run_middle();
		any prepareLevel(int a1);
		any getBlockColors();
		any getItemColors();
		any forceLeaderboardSave(int a1);
		any addPendingClientTextureRequest(std::wstring const& a1);
		any handleClientTextureReceived(std::wstring const& a1);
		any isUsingDefaultSkin();
		any getCurrentTexturePackId();
		any getMaterialTable();
		any getStructureManager();
		any fjReloadTexturePack();
		any GetPlayerByPlayerIndex(int a1);
		any GetSpectateMode();
		any GetSpectateEntity();
		any SetupMiniGameInstance(/*MiniGameDef */void* const a1, int a2);
		any GetFirstMiniGame();
		any showOnlyReducedInfo();
		any GetGhostController();
	};
	app* getInstance() {
		return *(app**)0x014CF2E4;
	}
	

	enum class TimeGranularity {
		MILLISECONDS,
		UNUSED, // not seconds.
		NANOSECONDS,

	};
	class System {
	public:
		/// <summary>
		/// Initializes all the bytes of the specified array to zero.
		/// </summary>
		/// <typeparam name="arrayWithLength">array</typeparam>
		/// <typeparam name="size">size</typeparam>
		/// <param name="a">array</param>
		/// <returns></returns>
		template <int size, typename arrayWithLength>
		static size_t clear(arrayWithLength(&a)[size]);

		/// <summary>
		/// Copies data.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="src"></param>
		/// <param name="dest"></param>
		/// <param name="length"></param>
		/// <returns></returns>
		template <typename T>
		static unsigned int copyMem(T* src, T* dest, size_t length);

		template <int size, typename arrayWithLength>
		static unsigned int arraycopy(arrayWithLength(&source)[size], arrayWithLength(&dest)[size], int srcIndex, int index, unsigned int count);
		/// <summary>
		/// Retrieves the active system time; (since boot) in the specified granularity.
		/// </summary>
		/// <param name="e">Granularity kind</param>
		/// <returns>ulonglong</returns>
		static uint64_t System::processTime(TimeGranularity e);
		/// <summary>
		/// Retrieves the active system time; (since boot) in seconds.
		/// </summary>
		/// <returns>ulonglong</returns>
		static uint64_t System::processTimeInSeconds();
		/// <summary>
		/// Retrieves the active system time; (since boot) in milliseconds.
		/// </summary>
		/// <returns>ulonglong</returns>
		static uint64_t System::processTimeInMillisecs();
		/// <summary>
		/// Retrieves the active system time; (since boot) in nanos.
		/// </summary>
		/// <returns>ulonglong</returns>
		static uint64_t System::processTimeInNanosecs();
		/// <summary>
		/// Checks if the caller context is being executed on the main game's thread.
		/// </summary>
		/// <returns>boolean</returns>
		static bool System::isMainThread();

		/// <summary>
		/// System calls the processor to yield resources and sleep the specified milliseconds.
		/// </summary>
		/// <param name="milliseconds">uint</param>
		static void System::Sleep(long milliseconds);
	};
}

namespace mth {
    static double pi = 3.1415926535897931;
    static double deg2rad = pi / 180.0f;

    float degrees(float Radians);
    float radians(float degress);
    float clamp(float x, float m, float mx);
    float clamp(float value, float min);
    /**
     * Compares two floating-point numbers for equality.
     *
     * @param a The first float to compare.
     * @param b The second float to compare.
     * @return true if the values are equal, false otherwise.
     */
    bool equal(float a, float b);
    float atan2(float x, float y);
    /**
     * Computes the square root of a floating-point number.
     *
     * @param x The number for which to compute the square root.
     * @return The square root of x.
     */
    float fsqrt(float x);

    /**
     * Computes the greatest integer value less than or equal to x.
     *
     * @param x The number to process.
     * @return The largest integer not greater than x.
     */
    float floor(float x);

    /**
     * Computes the cosine of an angle x (in radians).
     *
     * @param x The angle in radians.
     * @return The cosine of x.
     */
    float cos(float x);

    /**
     * Computes the sine of an angle x (in radians).
     *
     * @param x The angle in radians.
     * @return The sine of x.
     */
    float sin(float x);

    /**
     * Computes the square root of x (identical to fsqrt).
     *
     * @param x The number for which to compute the square root.
     * @return The square root of x.
     */
    float sqrt(float x);

    /**
     * Computes the tangent of an angle x (in radians), defined as sin(x) / cos(x).
     *
     * @param x The angle in radians.
     * @return The tangent of x.
     */
    float tan(float x);

    /**
     * Computes the smallest integer greater than or equal to x.
     *
     * @param x The number to process.
     * @return The smallest integer not less than x.
     */
    float ceil(float x);

    /**
     * A function that likely gradually approaches a value, often used in animations or calculations.
     *
     * @param x The input value.
     * @return The processed value based on x.
     */
    float approach(float x);

    /**
     * Compares two floating-point numbers for near equality, considering a small margin of error.
     *
     * @param x The first float to compare.
     * @param y The second float to compare.
     * @return true if x is approximately equal to y, false otherwise.
     */
    bool almostEquals(float x, float y);

    /**
     * Rounds x up based on y, possibly considering precision or a threshold.
     *
     * @param x The number to round.
     * @param y The threshold for rounding.
     * @return The rounded value.
     */
    float roundUp(float x, float y);

    /**
     * Returns the absolute value of x if it's greater than max, or max otherwise.
     *
     * @param x The value to compare.
     * @param max The maximum value.
     * @return The absolute value of x or max, whichever is larger.
     */
    float absmax(float x, float max);

    /**
     * Computes the floor of x in a fast, optimized manner.
     *
     * @param x The number to process.
     * @return The largest integer less than or equal to x.
     */
    float fastFloor(float x);

    /**
     * Likely computes the inverse tangent (atan2) of x, with results cached for performance.
     *
     * @param x The value to compute the inverse tangent.
     * @return The inverse tangent of x.
     */
    float cachedAtan2(float x);

    /**
     * Converts HSV (Hue, Saturation, Value) color to RGB (Red, Green, Blue).
     *
     * @param hue The hue of the color.
     * @param saturation The saturation of the color.
     * @param brightness The brightness of the color.
     * @return The RGB color representation.
     */
    double hsvToRgb(double hue, double saturation, double brightness);

    /**
     * Recursively computes base raised to the power of exp. Handles negative exponents by using the reciprocal.
     *
     * @param base The base number.
     * @param exp The exponent.
     * @return The result of base raised to the power of exp.
     */
    double rpow(double base, int exp);
}
