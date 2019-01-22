#pragma once
#include "app/common.hpp"
#include "widgets/OpaqueWidget.hpp"
#include "widgets/FramebufferWidget.hpp"
#include "app/CableContainer.hpp"
#include "app/ModuleWidget.hpp"


namespace rack {


struct RackWidget : OpaqueWidget {
	FramebufferWidget *rails;
	// Only put ModuleWidgets in here
	Widget *moduleContainer;
	// Only put CableWidgets in here
	CableContainer *cableContainer;
	/** The currently loaded patch file path */
	std::string patchPath;
	/** The last mouse position in the RackWidget */
	math::Vec mousePos;

	RackWidget();
	~RackWidget();

	/** Completely clear the rack's modules and cables */
	void clear();
	/** Clears the rack and loads the template patch */
	void reset();
	void loadDialog();
	void saveDialog();
	void saveAsDialog();
	void saveTemplate();
	/** If `lastPath` is defined, ask the user to reload it */
	void revert();
	/** Disconnects all cables */
	void disconnect();
	void save(std::string filename);
	void load(std::string filename);
	json_t *toJson();
	void fromJson(json_t *rootJ);
	void pastePresetClipboard();

	void addModule(ModuleWidget *m);
	void addModuleAtMouse(ModuleWidget *m);
	/** Removes the module and transfers ownership to the caller */
	void removeModule(ModuleWidget *m);
	/** Sets a module's box if non-colliding. Returns true if set */
	bool requestModuleBox(ModuleWidget *m, math::Rect requestedBox);
	/** Moves a module to the closest non-colliding position */
	bool requestModuleBoxNearest(ModuleWidget *m, math::Rect requestedBox);
	ModuleWidget *getModule(int moduleId);

	void step() override;
	void draw(NVGcontext *vg) override;

	void onHover(const event::Hover &e) override;
	void onDragHover(const event::DragHover &e) override;
	void onButton(const event::Button &e) override;
	void onZoom(const event::Zoom &e) override;
};


} // namespace rack
