/*
 * Copyright (C) 2011 Georgia Institute of Technology, University of Utah,
 * Weill Cornell Medical College
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * This is a template implementation file for a user module derived from
 * DefaultGUIModel with a custom GUI.
 */

#include "limiter.h"
#include <iostream>
#include <main_window.h>

extern "C" Plugin::Object*
createRTXIPlugin(void)
{
  return new Limiter();
}

static DefaultGUIModel::variable_t vars[] = {
  {
    "Upper Limit", "",
    DefaultGUIModel::PARAMETER | DefaultGUIModel::DOUBLE,
  },
  {
    "Lower Limit", "",
    DefaultGUIModel::PARAMETER | DefaultGUIModel::DOUBLE,
  },
  {
    "x-in", "",
    DefaultGUIModel::INPUT,
  },
  {
    "x-out", "",
    DefaultGUIModel::OUTPUT,
  },

};

static size_t num_vars = sizeof(vars) / sizeof(DefaultGUIModel::variable_t);

Limiter::Limiter(void)
  : DefaultGUIModel("Limiter with Custom GUI", ::vars, ::num_vars)
{
  setWhatsThis("<p><b>Limiter:</b><br>QWhatsThis description.</p>");
  DefaultGUIModel::createGUI(vars,
                             num_vars); // this is required to create the GUI
  customizeGUI();
  initParameters();
  update(INIT); // this is optional, you may place initialization code directly
                // into the constructor
  refresh();    // this is required to update the GUI with parameter and state
                // values
  QTimer::singleShot(0, this, SLOT(resizeMe()));
}

Limiter::~Limiter(void)
{
}

void
Limiter::execute(void)
{
  double x = input(0);
  if (x>upper_lim){	x=upper_lim;  }
  if (x<lower_lim){	x=lower_lim; }
  output(0) = x;

  return;
}

void
Limiter::initParameters(void)
{
  some_parameter = 0;
  some_state = 0;
  upper_lim = 5;
  lower_lim = 0;
}

void
Limiter::update(DefaultGUIModel::update_flags_t flag)
{
  switch (flag) {
    case INIT:
      period = RT::System::getInstance()->getPeriod() * 1e-6; // ms
      setParameter("Upper Limit", upper_lim);
      setParameter("Lower Limit", lower_lim);
      break;

    case MODIFY:
      some_parameter = getParameter("GUI label").toDouble();
	  upper_lim = getParameter("Upper Limit").toDouble();
	  lower_lim = getParameter("Lower Limit").toDouble();

      break;

    case UNPAUSE:
      break;

    case PAUSE:
      break;

    case PERIOD:
      period = RT::System::getInstance()->getPeriod() * 1e-6; // ms
      break;

    default:
      break;
  }
}

void
Limiter::customizeGUI(void)
{
  QGridLayout* customlayout = DefaultGUIModel::getLayout();

  QGroupBox* button_group = new QGroupBox;

  QPushButton* abutton = new QPushButton("Button A");
  QPushButton* bbutton = new QPushButton("Button B");
  QHBoxLayout* button_layout = new QHBoxLayout;
  button_group->setLayout(button_layout);
  button_layout->addWidget(abutton);
  button_layout->addWidget(bbutton);
  QObject::connect(abutton, SIGNAL(clicked()), this, SLOT(aBttn_event()));
  QObject::connect(bbutton, SIGNAL(clicked()), this, SLOT(bBttn_event()));

  customlayout->addWidget(button_group, 0, 0);
  setLayout(customlayout);
}

// functions designated as Qt slots are implemented as regular C++ functions
void
Limiter::aBttn_event(void)
{
}

void
Limiter::bBttn_event(void)
{
}
