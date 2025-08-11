interface LineProps {
    customStyling?: string
}

export default function Line({customStyling} : LineProps) {
    return(
        <div className={`bg-neutral-700 w-full h-px ${customStyling}`}></div>
    );
};
