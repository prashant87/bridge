#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <iostream>
#include <iomanip>

#include "ImguiManager.h"
#include "plot_maker.h"
#include "classifier.h"
#include "fitter.h"
#include "al_wrap.h"

class ImguiExample : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    PlotMaker plotMaker;
    AlWrap    alWrap;
    Classifier classifier;
    Fitter     fitter;
    std::vector<float> data[7];

    bool classificationEnabled;
    bool classificationTraining;

    bool fittingEnabled;
    bool fittingTraining;

    void plotRegressionWindow();
    void plotFitterWindow();

    void plotsWindow();
    void plotGroupCtrls( const char * title );
    void plotGroup( int index, const char * title, const ImVec2 & sz=ImVec2( 320, 240 ), bool sameLine=false );

    void plotsStdWindow();
    void plotStdGroupCtrls( const char * title );
    void plotStdGroup( int index, const char * title, const ImVec2 & sz=ImVec2( 320, 240 ), bool sameLine=false );

    ImguiExample() : OgreBites::ApplicationContext("Electrical analysis")
    {
        classificationEnabled = false;
        classificationTraining = true;

        fittingEnabled  = false;
        fittingTraining = true;
    }

    bool frameStarted(const Ogre::FrameEvent& evt)
    {
        OgreBites::ApplicationContext::frameStarted(evt);

        Ogre::ImguiManager::getSingleton().newFrame(
            evt.timeSinceLastFrame,
            Ogre::Rect(0, 0, getRenderWindow()->getWidth(), getRenderWindow()->getHeight()));

        ImGui::ShowTestWindow();
        plotsWindow();
        plotsStdWindow();
        plotRegressionWindow();
        plotFitterWindow();

        return true;
    }

    void setup()
    {
        OgreBites::ApplicationContext::setup();
        addInputListener(this);

        Ogre::ImguiManager::createSingleton();
        addInputListener(Ogre::ImguiManager::getSingletonPtr());

        // get a pointer to the already created root
        Ogre::Root* root = getRoot();
        Ogre::SceneManager* scnMgr = root->createSceneManager();
        Ogre::ImguiManager::getSingleton().init(scnMgr);

        // register our scene with the RTSS
        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(scnMgr);


        Ogre::Light* light = scnMgr->createLight("MainLight");
        Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        lightNode->setPosition(0, 10, 15);
        lightNode->attachObject(light);


        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        camNode->setPosition(0, 0, 15);
        camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

        Ogre::Camera* cam = scnMgr->createCamera("myCam");
        cam->setNearClipDistance(5); // specific to this sample
        cam->setAutoAspectRatio(true);
        camNode->attachObject(cam);
        getRenderWindow()->addViewport(cam);

        /*Ogre::Entity* ent = scnMgr->createEntity("Sinbad.mesh");
        Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
        node->attachObject(ent);*/

        alWrap.createStream( &plotMaker );
    }

    bool keyPressed(const OgreBites::KeyboardEvent& evt)
    {
        if (evt.keysym.sym == 27)
        {
            getRoot()->queueEndRendering();
        }
        if ( classificationEnabled && classificationTraining )
        {
            if ( ( evt.keysym.sym >= '1' ) && ( evt.keysym.sym <= '3' ) )
            {
                int category = evt.keysym.sym - '1';
                int rawQty, stdQty, step;
                classifier.dimensions( rawQty, stdQty, step );
                std::vector<float> data;
                plotMaker.classificationSample( rawQty, stdQty, step, data );
                classifier.push( category, data );
            }
        }
        if ( fittingEnabled && fittingTraining )
        {
            if ( ( evt.keysym.sym >= '1' ) && ( evt.keysym.sym <= '9' ) )
            {
                const float value = static_cast<float>(evt.keysym.sym - '1')/9.0;
                int rawQty, stdQty, step;
                fitter.dimensions( rawQty, stdQty, step );
                std::vector<float> data;
                plotMaker.classificationSample( rawQty, stdQty, step, data );
                fitter.push( value, data );
            }
        }
        return true;
    }
};


int main(int argc, char *argv[])
{
    ImguiExample app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();

    return 0;
}


void ImguiExample::plotsWindow()
{
    if ( ImGui::Begin( "Plots", 0 ) )
    {
        plotGroupCtrls( "Controls" );
        //plotGroup( 0, "Plot A", ImVec2(0, 180), false );
        //plotGroup( 1, "Plot B", ImVec2(0, 180), true );
        //plotGroup( 2, "Plot C", ImVec2(0, 180), false );
        plotGroup( 3, "Plot D", ImVec2( 0, 180 ), true );
        plotGroup( 4, "Plot E", ImVec2( 0, 180 ), true );
        plotGroup( 5, "Plot F", ImVec2( 0, 180 ), true );
        //plotGroup( 6, "Plot G", ImVec2( 0, 180 ), true );
    }
    ImGui::End();
}


void ImguiExample::plotGroupCtrls( const char * title )
{
    ImGui::BeginGroup();
    {
        ImGui::Button( "Click me" );
    }
    ImGui::EndGroup();
}

void ImguiExample::plotGroup( int index, const char * title, const ImVec2 & sz, bool sameLine )
{
    ImGui::BeginGroup();
        ImGui::PushID( index );
        if ( ImGui::Button( "up" ) )
            plotMaker.moveUp( index );
        ImGui::SameLine();
        if ( ImGui::Button( "+" ) )
            plotMaker.zoomIn( index );
        if ( ImGui::Button( "down" ) )
            plotMaker.moveDown( index );
        ImGui::SameLine();
        if ( ImGui::Button( "-" ) )
            plotMaker.zoomOut( index );
        if ( ImGui::Button( "|<" ) )
            plotMaker.setAudioSource( index );
        ImGui::PopID();
    ImGui::EndGroup();
    //if ( sameLine )
    //    ImGui::SameLine();

    ImGui::SameLine();
    //ImGui::SetNextWindowSizeConstraints( ImVec2(0, 0), sz );

    //ImGui::BeginGroup();
    {
        float vmin, vmax;
        plotMaker.limits( index, vmin, vmax );
        std::vector<float> & data = this->data[index];
        plotMaker.array( index, data );
        float * arr = data.data();
        const int qty = data.size();
        ImGui::PlotLines( "", arr, qty, 0, title, vmin, vmax, sz );
    }
    //ImGui::EndGroup();

    if ( ImGui::IsItemHovered() )
    {
        ImGui::BeginTooltip();
        {
            ImGui::TextUnformatted( title );
        }
        ImGui::EndTooltip();
    }
}

void ImguiExample::plotsStdWindow()
{
    if ( ImGui::Begin( "Plots std", 0 ) )
    {
        plotGroupCtrls( "Controls" );
        //plotStdGroup( 0, "Plot std A", ImVec2(0, 180), false );
        //plotStdGroup( 1, "Plot std B", ImVec2(0, 180), true );
        //plotStdGroup( 2, "Plot std C", ImVec2(0, 180), false );
        plotStdGroup( 3, "Plot std D", ImVec2( 0, 180 ), true );
        plotStdGroup( 4, "Plot std E", ImVec2( 0, 180 ), true );
        plotStdGroup( 5, "Plot std F", ImVec2( 0, 180 ), true );
        //plotStdGroup( 6, "Plot std G", ImVec2( 0, 180 ), true );
    }

    ImGui::End();
}

void ImguiExample::plotStdGroupCtrls( const char * title )
{

}

void ImguiExample::plotStdGroup( int index, const char * title, const ImVec2 & sz, bool sameLine )
{
    ImGui::BeginGroup();
        ImGui::PushID( index + 7 );
        if ( ImGui::Button( "up" ) )
            plotMaker.stdMoveUp( index );
        ImGui::SameLine();
        if ( ImGui::Button( "+" ) )
            plotMaker.stdZoomIn( index );
        if ( ImGui::Button( "down" ) )
            plotMaker.stdMoveDown( index );
        ImGui::SameLine();
        if ( ImGui::Button( "-" ) )
            plotMaker.stdZoomOut( index );
        ImGui::PopID();
    ImGui::EndGroup();
    //if ( sameLine )
    //    ImGui::SameLine();

    ImGui::SameLine();
    //ImGui::SetNextWindowSizeConstraints( ImVec2(0, 0), sz );

    //ImGui::BeginGroup();
    {
        float vmin, vmax;
        plotMaker.stdLimits( index, vmin, vmax );
        std::vector<float> & data = this->data[index];
        plotMaker.arrayStd( index, data );
        float * arr = data.data();
        const int qty = data.size();
        ImGui::PlotLines( "", arr, qty, 0, title, vmin, vmax, sz );
    }
    //ImGui::EndGroup();

    if ( ImGui::IsItemHovered() )
    {
        ImGui::BeginTooltip();
        {
            ImGui::TextUnformatted( title );
        }
        ImGui::EndTooltip();
    }
}

void ImguiExample::plotRegressionWindow()
{
    if ( ImGui::Begin( "Regression", 0 ) )
    {
        ImGui::BeginGroup();
        {
            ImGui::Checkbox( "Enabled", &classificationEnabled );
            if ( classificationEnabled )
            {
                ImGui::Checkbox( "Training", &classificationTraining );
                if ( classificationTraining )
                {
                    ImGui::SameLine();
                    ImGui::Text( "Use \"1\", \"2\", \"3\" buttons to add training data to a classifier" );
                }
                else
                {
                    int rawQty, stdQty, step;
                    classifier.dimensions( rawQty, stdQty, step );
                    std::vector<float> data;
                    plotMaker.classificationSample( rawQty, stdQty, step, data );
                    //int category = classifier.classify( data );

                    // For debugging.
                    static int category = 0;
                    category += 1;
                    if ( category > 2 )
                        category = 0;

                    ImGui::Text( "Category %i", category );
                    static Ogre::TexturePtr texture;
                    try {
                        if ( category == 1 )
                        {
                            texture = Ogre::TextureManager::getSingleton().getByName( "engaged.png" );
                            if ( !texture )
                                texture = Ogre::TextureManager::getSingleton().load( "engaged.png", "General" );
                        }
                        else if ( category == 2 )
                        {
                            texture = Ogre::TextureManager::getSingleton().getByName( "disengaged.png" );
                            if ( !texture )
                                texture = Ogre::TextureManager::getSingleton().load( "disengaged.png", "General" );
                        }
                    } catch(...)
                    {}
                    if ( texture )
                    {
                        Ogre::ResourceHandle handle = texture->getHandle();
                        ImGui::Image( (ImTextureID)handle, ImVec2( 512, 512 ) );
                    }
                }
            }
        }
        ImGui::EndGroup();

        ImGui::BeginGroup();
        {
            if ( ImGui::Button( "Load" ) )
            {
                classifier.load( "./classifier.data" );
            }
            ImGui::SameLine();
            if ( ImGui::Button( "Save" ) )
            {
                classifier.save( "./classifier.data" );
            }
        }
        ImGui::EndGroup();
    }

    ImGui::End();
}

void ImguiExample::plotFitterWindow()
{
    if ( ImGui::Begin( "Fitting", 0 ) )
    {
        ImGui::BeginGroup();
        {
            ImGui::Checkbox( "Enabled", &fittingEnabled );
            if ( fittingEnabled )
            {
                ImGui::Checkbox( "Training", &fittingTraining );
                if ( fittingTraining )
                {
                    ImGui::SameLine();
                    ImGui::Text( "Use \"1\", through \"9\" buttons to describe current hand pose" );
                }
                else
                {
                    int rawQty, stdQty, step;
                    fitter.dimensions( rawQty, stdQty, step );
                    std::vector<float> data;
                    plotMaker.classificationSample( rawQty, stdQty, step, data );
                    //const float value = fitter.classify( data );

                    // Debugging.
                    static float value = 0.0f;
                    value += 0.01f;
                    if ( value >= 1.0f )
                        value = 0.0f;

                    ImGui::Text( "Hand pose: %3.2f", value );
                    int v = static_cast<int>( 99.0f * value );
                    if ( v < 0 )
                        v = 0;
                    else if ( v > 99 )
                        v = 99;
                    v += 1;
                    Ogre::stringstream ss;
                    ss << "Image" << std::setfill('0') << std::setw( 4 ) << v << ".png";
                    const Ogre::String stri = ss.str();

                    static Ogre::TexturePtr texture;
                    try {
                        texture = Ogre::TextureManager::getSingleton().getByName( stri );
                        if ( !texture )
                            texture = Ogre::TextureManager::getSingleton().load( stri, "General" );
                    } catch (...)
                    {}
                    if ( texture )
                    {
                        Ogre::ResourceHandle handle = texture->getHandle();
                        ImGui::Image( (ImTextureID)handle, ImVec2( 512, 512 ) );
                    }
                }
            }
        }
        ImGui::EndGroup();

        ImGui::BeginGroup();
        {
            if ( ImGui::Button( "Load" ) )
            {
                fitter.load( "./fitter.data" );
            }
            ImGui::SameLine();
            if ( ImGui::Button( "Save" ) )
            {
                fitter.save( "./fitter.data" );
            }
        }
        ImGui::EndGroup();
    }

    ImGui::End();
}


