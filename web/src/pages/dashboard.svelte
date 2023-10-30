<script>
import Card from "../components/layout/card.svelte"
import { current } from "../store/measurments";
</script>

<Card>
    <h1>CO2 {$current.co2} ppm</h1>
</Card>
<Card>
    <h1>Temperatur {$current.temp} °C</h1>
</Card>
<Card>
    <h1>Luftfeutigkeit {$current.hum} H%</h1>
</Card>