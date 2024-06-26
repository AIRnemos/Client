import { Link, Outlet, createRootRoute } from "@tanstack/react-router";
import {
  Home,
  Menu,
  Settings,
} from "lucide-react"

import { Button } from "@/components/ui/button"
import { Sheet, SheetContent, SheetTrigger } from "@/components/ui/sheet"

export const Route = createRootRoute({
    component: () => (
      <div className="grid min-h-screen w-full md:grid-cols-[220px_1fr] lg:grid-cols-[280px_1fr]">
        <div className="hidden border-r bg-muted/40 md:block">
          <div className="flex h-full max-h-screen flex-col gap-2">
            <div className="flex h-14 items-center border-b px-4 lg:h-[60px] lg:px-6">
                <span className="font-semibold">AIRnemos</span> - %name%
            </div>
            <div className="flex-1">
              <nav className="grid items-start px-2 text-sm font-medium lg:px-4">
                <Link
                  to="/"
                  activeProps={{ className: "bg-muted text-primary" }}
                  inactiveProps={{ className: "text-muted-foreground" }}
                  className="flex items-center gap-3 rounded-lg px-3 py-2 transition-all hover:text-primary"
                >
                  <Home className="h-4 w-4" />
                  Dashboard
                </Link>
                <Link
                  to="/settings"
                  activeProps={{ className: "bg-muted text-primary" }}
                  inactiveProps={{ className: "text-muted-foreground" }}
                  className="flex items-center gap-3 rounded-lg px-3 py-2 transition-all hover:text-primary"
                >
                  <Settings className="h-4 w-4" />
                  Settings
                </Link>
              </nav>
            </div>
          </div>
        </div>
        <div className="flex flex-col">
          <header className="flex h-14 items-center gap-4 border-b bg-muted/40 px-4 md:hidden">
            <Sheet>
              <SheetTrigger asChild>
                <Button
                  variant="ghost"
                  size="icon"
                  className="shrink-0"
                >
                  <Menu className="h-5 w-5" />
                  <span className="sr-only">Toggle navigation menu</span>
                </Button>
              </SheetTrigger>
              <SheetContent side="left" className="flex flex-col">
                <nav className="grid gap-2 text-lg font-medium">
                  <div
                    className="flex items-center gap-2 text-lg"
                  >
                    <span className="font-semibold">AIRnemos</span> - %name%
                  </div>
                  <Link
                    to="/"
                    activeProps={{ className: "bg-muted text-foreground" }}
                    inactiveProps={{ className: "text-muted-foreground" }}
                    className="mx-[-0.65rem] flex items-center gap-4 rounded-xl px-3 py-2 hover:text-foreground"
                  >
                    <Home className="h-4 w-4" />
                    Dashboard
                  </Link>
                  <Link
                    to="/settings"
                    activeProps={{ className: "bg-muted text-foreground" }}
                    inactiveProps={{ className: "text-muted-foreground" }}
                    className="mx-[-0.65rem] flex items-center gap-4 rounded-xl px-3 py-2 hover:text-foreground"
                  >
                    <Settings className="h-4 w-4" />
                    Settings
                  </Link>
                </nav>
              </SheetContent>
            </Sheet>
            <div>
              <span className="font-semibold">AIRnemos</span> - %name%
            </div>
          </header>
          <main className="flex flex-1 flex-col gap-4 p-4 lg:gap-6 lg:p-6">
            <Outlet></Outlet>
          </main>
        </div>
      </div>
    ),
  })
