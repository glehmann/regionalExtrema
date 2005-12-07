#ifndef __itkValuedRegionalMinimaImageFilter_h
#define __itkValuedRegionalMinimaImageFilter_h

#include "itkValuedRegionalExtremaImageFilter.h"
#include "itkNumericTraits.h"

namespace itk {

template <class TInputImage, class TOutputImage>
class ITK_EXPORT ValuedRegionalMinimaImageFilter :
    public
    ValuedRegionalExtremaImageFilter<TInputImage, TOutputImage,
			       std::less<typename TInputImage::PixelType>,
			       std::less<typename TOutputImage::PixelType>
    >
{
public:
  typedef ValuedRegionalMinimaImageFilter Self;
  typedef ValuedRegionalExtremaImageFilter<TInputImage, TOutputImage,
				     std::less<typename TInputImage::PixelType>,
				     std::less<typename TOutputImage::PixelType>  > Superclass;

  typedef SmartPointer<Self>   Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);


protected:
  ValuedRegionalMinimaImageFilter() 
  {
    SetMarkerValue(NumericTraits<typename TOutputImage::PixelType>::max());
  }
  virtual ~ValuedRegionalMinimaImageFilter() {}

private:
  ValuedRegionalMinimaImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented



}; // end ValuedRegionalMinimaImageFilter

} //end namespace itk
#endif
