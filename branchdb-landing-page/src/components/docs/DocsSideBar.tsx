import { onest } from "../../app/layout";

export default function DocsSideBar() {

    // Sidebar Items list
    const documentationSections = [
        {
            sectionTitle: "Getting Started",
            sectionItems: [
                {
                    itemName: "What is BranchDB?",
                    anchorLink: "/docs"
                },
                {
                    itemName: "Installation",
                    anchorLink: "#installation"
                },
                {
                    itemName: "Quickstart",
                    anchorLink: "#quickstart"
                },
            ]
        },
        {
            sectionTitle: "Core Concepts",
            sectionItems: [
                {
                    itemName: "Commands",
                    anchorLink: "/docs/concepts"
                },
                {
                    itemName: "TTL",
                    anchorLink: "/docs/concepts#ttl"
                },
                // {
                //     itemName: "Persistence",
                //     anchorLink: "#persistence"
                // },
                // {
                //     itemName: "Authentication",
                //     anchorLink: "#authentication"
                // },
            ]
        },
        {
            sectionTitle: "Client SDK's",
            sectionItems: [
                {
                    itemName: "JavaScript SDK",
                    anchorLink: "/docs/sdk"
                }
            ]
        },
    ];

    return (
        <div className={`h-screen w-64 overflow-y-scroll overflow-x-hidden custom-scrollbar text-gray-400 p-6 ${onest.className} border-r border-r-neutral-700`}>
            <div className="flex flex-col gap-y-6">
                {
                    documentationSections.map((sectionItem, sec_index) => (
                        <div key={sec_index} className="flex flex-col gap-y-2">
                            <p className="font-bold text-lg text-white tracking-wide">{sectionItem.sectionTitle}</p>
                            <div className="flex flex-col pl-4">
                                {
                                    sectionItem.sectionItems.map((item, index) => (
                                        <a 
                                            key={index} 
                                            href={item.anchorLink} 
                                            className="py-1 text-sm hover:text-white transition-colors duration-150"
                                        >
                                            {item.itemName}
                                        </a>
                                    ))
                                }
                            </div>
                        </div>
                    ))
                }
            </div>
        </div>
    );
};