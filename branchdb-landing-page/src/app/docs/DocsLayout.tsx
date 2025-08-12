import DocsSideBar from "@/components/docs/DocsSideBar";
import { onest } from "../layout";

export default function DocsLayout({ children }: Readonly<{
    children: React.ReactNode;
}>) {
    return (
        <div className={`h-screen w-full px-6 bg-black flex flex-col overflow-y-scroll custom-scrollbar rounded-md relative pt-[150px] ${onest.className}`}>
            <div className="flex justify-start items center gap-8">
                <DocsSideBar />
                {children}
            </div>
        </div>
    );
};
