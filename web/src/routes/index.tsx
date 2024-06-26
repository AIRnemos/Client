import { createFileRoute } from '@tanstack/react-router'
import { useMeasurement } from '../hook/measurement'
import { Card, CardContent, CardDescription, CardHeader, CardTitle } from '@/components/ui/card'
import { Line, LineChart, ResponsiveContainer, Tooltip, XAxis, YAxis } from 'recharts'

export const Route = createFileRoute('/')({
  component: route
})

const dateFormatter = (date: any) => {
  if (!(date instanceof Date)) return date

  return `${date.getHours()}:${date.getMinutes()}:${date.getSeconds()}`
};

function route() {
    const { co2, temp, hum, history } = useMeasurement()

    return <>
      <div className="grid gap-4 sm:grid-cols-2 md:grid-cols-4 lg:grid-cols-2 xl:grid-cols-4">
        <Card
          className="sm:col-span-2"
        >
          <CardHeader className="pb-3 sm:flex-row md:flex-col lg:flex-row">
            <CardDescription>CO2</CardDescription>
            <span className='flex-grow hidden sm:block md:hidden lg:block'></span>
            <CardTitle className="text-4xl ">{co2} ppm</CardTitle>
          </CardHeader>
        </Card>
        <Card>
          <CardHeader className="pb-2">
            <CardDescription>Temperatur</CardDescription>
            <CardTitle className="text-4xl">{temp} °C</CardTitle>
          </CardHeader>
        </Card>
        <Card>
        <CardHeader className="pb-2">
            <CardDescription>Luftfeuchtigkeit</CardDescription>
            <CardTitle className="text-4xl">{hum} %H</CardTitle>
          </CardHeader>
        </Card>
      </div>
      <Card>
        <CardHeader className="flex flex-row items-center justify-between space-y-0 pb-2">
          <CardTitle className="text-base font-normal">Total Revenue</CardTitle>
        </CardHeader>
        <CardContent>
          <div className='h-[25rem] lg:h-[30rem] xl:h-[30rem] 2xl:h-[48rem]'>
            <p>{Math.round(Math.pow(window.innerWidth, 2)/ 200_000)}</p>
            <ResponsiveContainer  width="100%" height="100%">
              <LineChart
                data={history}
                height={800}
                width={800}
              >
                <Tooltip />
                <YAxis />
                <XAxis 
                  dataKey="date"
                  tickFormatter={dateFormatter}
                />
                <Line
                  type="monotone"
                  dataKey="co2"
                  dot={false}
                />
              </LineChart>
            </ResponsiveContainer>
          </div>
        </CardContent>
      </Card>
    </>
}