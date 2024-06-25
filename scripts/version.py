#    AIRnemos is a software for CO2 meter.
#    Copyright (C) 2023-2024 Quentin Schuster
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.

import os

VERSION = os.getenv('VERSION', '0.0.0')

if not os.path.exists("VERSION"):
    open("VERSION", "x")

with open("VERSION", "r+") as f:
    data = f.read()
    f.seek(0)
    f.write(VERSION)
    f.truncate()
    f.close()