namespace vgui
{
	typedef unsigned long HFont;


	typedef unsigned long HScheme;
	typedef unsigned long HTexture;

	class IBorder;
	class IImage;

	class IScheme : public IBaseInterface
	{
	public:
		// gets a string from the default settings section
		virtual const char *GetResourceString(const char *stringName) = 0;

		// returns a pointer to an existing border
		virtual IBorder *GetBorder(const char *borderName) = 0;

		// returns a pointer to an existing font
		virtual HFont GetFont(const char *fontName, bool proportional = false) = 0;

		// inverse font lookup
		virtual char const *GetFontName(const HFont& font) = 0;

		// colors
		virtual Color GetColor(const char *colorName, Color defaultColor) = 0;

		// Get the number of borders
		virtual int GetBorderCount() const = 0;

		// Get the border at the given index
		virtual IBorder *GetBorderAtIndex(int iIndex) = 0;

		// Get the number of fonts
		virtual int GetFontCount() const = 0;

		// Get the font at the given index
		virtual HFont GetFontAtIndex(int iIndex) = 0;

		// Get color data
		virtual const KeyValues *GetColorData() const = 0;
	};
	class ISchemeManager : public IBaseInterface
	{
	public:
		// loads a scheme from a file
		// first scheme loaded becomes the default scheme, and all subsequent loaded scheme are derivitives of that
		virtual HScheme LoadSchemeFromFile(const char *fileName, const char *tag) = 0;

		// reloads the scheme from the file - should only be used during development
		virtual void ReloadSchemes() = 0;

		// reloads scheme fonts
		virtual void ReloadFonts() = 0;

		// returns a handle to the default (first loaded) scheme
		virtual HScheme GetDefaultScheme() = 0;

		// returns a handle to the scheme identified by "tag"
		virtual HScheme GetScheme(const char *tag) = 0;

		// returns a pointer to an image
		virtual IImage *GetImage(const char *imageName, bool hardwareFiltered) = 0;
		virtual HTexture GetImageID(const char *imageName, bool hardwareFiltered) = 0;

		// This can only be called at certain times, like during paint()
		// It will assert-fail if you call it at the wrong time...

		// FIXME: This interface should go away!!! It's an icky back-door
		// If you're using this interface, try instead to cache off the information
		// in ApplySchemeSettings
		virtual IScheme *GetIScheme(HScheme scheme) = 0;

		// unload all schemes
		virtual void Shutdown(bool full = true) = 0;

		// gets the proportional coordinates for doing screen-size independant panel layouts
		// use these for font, image and panel size scaling (they all use the pixel height of the display for scaling)
		virtual int GetProportionalScaledValue(int normalizedValue) = 0;
		virtual int GetProportionalNormalizedValue(int scaledValue) = 0;

		// loads a scheme from a file
		// first scheme loaded becomes the default scheme, and all subsequent loaded scheme are derivitives of that
		virtual HScheme LoadSchemeFromFileEx(VPANEL sizingPanel, const char *fileName, const char *tag) = 0;
		// gets the proportional coordinates for doing screen-size independant panel layouts
		// use these for font, image and panel size scaling (they all use the pixel height of the display for scaling)
		virtual int GetProportionalScaledValueEx(HScheme scheme, int normalizedValue) = 0;
		virtual int GetProportionalNormalizedValueEx(HScheme scheme, int scaledValue) = 0;

		// Returns true if image evicted, false otherwise
		virtual bool DeleteImage(const char *pImageName) = 0;
	};
};