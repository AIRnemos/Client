<script>
/*
    AIRnemos is a software for CO2 meter.
    Copyright (C) 2023 Quentin Schuster

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

import Card from "../components/layout/card.svelte"
import { current } from "../store/measurments";
</script>

<div class="row">
    <div class="grow">
        <Card>
            <span>CO2</span>
            <span>{$current.co2} ppm</span>
        </Card>
    </div>
    <div class="card">
        <Card>
            <span>Temperatur</span>
            <span>{$current.temp} °C</span>
        </Card>
    </div>
    <div class="card">
        <Card>
            <span>Luftfeutigkeit</span>
            <span>{$current.hum} H%</span>
        </Card>
    </div>
</div>

<style lang="scss">
.row {
    display: flex;
    width: auto;
}

.card {
    width: 25%;
}

.grow {
    width: 50%;
}
</style>