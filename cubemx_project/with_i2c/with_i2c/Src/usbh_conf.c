/**
  ******************************************************************************
  * @file           : usbh_conf.c
  * @version        : v1.0_Cube
  * @brief          : This file implements the board support package for the USB host library
  ******************************************************************************
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usbh_core.h"


/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */


Error reading included file Src/usb_otg_hs_vars.tmp
The problematic instruction:
----------
==> include "Src/usb_otg_hs_vars.tmp" [on line 77, column 1 in usbhconf_c.ftl]
----------

Java backtrace for programmers:
----------
freemarker.template.TemplateException: Error reading included file Src/usb_otg_hs_vars.tmp
	at freemarker.core.Include.accept(Include.java:167)
	at freemarker.core.Environment.visit(Environment.java:208)
	at freemarker.core.ConditionalBlock.accept(ConditionalBlock.java:79)
	at freemarker.core.Environment.visit(Environment.java:208)
	at freemarker.core.MixedContent.accept(MixedContent.java:92)
	at freemarker.core.Environment.visit(Environment.java:208)
	at freemarker.core.Environment.process(Environment.java:188)
	at freemarker.template.Template.process(Template.java:237)
	at com.st.microxplorer.codegenerator.CodeEngine.freemarkerDo(CodeEngine.java:269)
	at com.st.microxplorer.codegenerator.CodeEngine.genCode(CodeEngine.java:190)
	at com.st.microxplorer.codegenerator.CodeGenerator.generateOutputCode(CodeGenerator.java:2913)
	at com.st.microxplorer.codegenerator.CodeGenerator.generateSpecificCode(CodeGenerator.java:2721)
	at com.st.microxplorer.codegenerator.CodeGenerator.generateSpecificCodeFile(CodeGenerator.java:1092)
	at com.st.microxplorer.codegenerator.CodeGenerator.generateCodeFiles(CodeGenerator.java:1229)
	at com.st.microxplorer.codegenerator.CodeGenerator.generateCode(CodeGenerator.java:935)
	at com.st.microxplorer.plugins.projectmanager.engine.ProjectBuilder.generateCode(ProjectBuilder.java:1029)
	at com.st.microxplorer.plugins.projectmanager.engine.ProjectBuilder.createCode(ProjectBuilder.java:913)
	at com.st.microxplorer.plugins.projectmanager.engine.ProjectBuilder.createProject(ProjectBuilder.java:444)
	at com.st.microxplorer.plugins.projectmanager.engine.GenerateProjectThread.run(GenerateProjectThread.java:41)
Caused by: java.io.FileNotFoundException: Template Src/usb_otg_hs_vars.tmp not found.
	at freemarker.template.Configuration.getTemplate(Configuration.java:489)
	at freemarker.core.Environment.getTemplateForInclusion(Environment.java:1459)
	at freemarker.core.Include.accept(Include.java:157)
	... 18 more
