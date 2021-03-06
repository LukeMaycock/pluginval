/*==============================================================================

  Copyright 2018 by Tracktion Corporation.
  For more information visit www.tracktion.com

   You may also use this code under the terms of the GPL v3 (see
   www.gnu.org/licenses).

   pluginval IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

 ==============================================================================*/

#include "../PluginTests.h"
#include "../TestUtilities.h"


//==============================================================================
/** Opens the plugin editor in various situations. */
struct EditorStressTest   : public PluginTest
{
    EditorStressTest()
        : PluginTest ("Editor stress", 6,
                      { Requirements::Thread::messageThread, Requirements::GUI::requiresGUI })
    {
    }

    void runTest (PluginTests& ut, AudioPluginInstance& instance) override
    {
        if (instance.hasEditor())
        {
            ScopedPluginDeinitialiser scopedPluginDeinitialiser (instance);

            {
                ut.logMessage ("Testing opening Editor with released processing");
                std::unique_ptr<AudioProcessorEditor> editor (instance.createEditor());

                if (editor)
                {
                    editor->addToDesktop (0);
                    editor->setVisible (true);
                }
            }

            {
                ut.logMessage ("Testing opening Editor with 0 sample rate and block size");
                instance.setPlayConfigDetails (instance.getTotalNumInputChannels(), instance.getTotalNumOutputChannels(), 0.0, 0);
                std::unique_ptr<AudioProcessorEditor> editor (instance.createEditor());

                if (editor)
                {
                    editor->addToDesktop (0);
                    editor->setVisible (true);
                }
            }
        }
    }
};

static EditorStressTest editorStressTest;
