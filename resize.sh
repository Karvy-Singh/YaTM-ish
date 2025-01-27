#!/bin/bash
value=$1
wmctrl -ir $value -b remove,maximized_vert,maximized_horz

